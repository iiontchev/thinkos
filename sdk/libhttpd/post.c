/* 
 * File:	post.c
 * Module:  
 * Project:	
 * Author:	Robinson Mittmann (bob@boreste.com, bobmittmann@gmail.com)
 * Target:	
 * Comment: 
 * Copyright(c) 2005-2009 BORESTE (www.boreste.com). All Rights Reserved.
 *
 */

#include "httpd-i.h"
#include "http_hdr.h"

#include <sys/param.h>

#define HEX2INT(C) (((C) <= '9') ? (C) - '0' : (C) - ('A' - 10))

/* On the World Wide Web, a query string is the part of a uniform resource
 * locator (URL) containing data that does not fit conveniently into a
 * hierarchical path structure. The query string commonly includes fields
 * added to a base URI by a Web browser or other client application, for
 * example as part of an HTML form.
 *
 * A typical URL containing a query string is as follows:
 *   http://example.com/over/there?name=ferret
 *
 * The main use of query strings is to contain the content of an HTML form,
 * also known as web form. In particular, when a form containing the fields
 * field1, field2, field3 is submitted, the content of the fields is encoded
 * as a query string as follows:
 *   field1=value1&field2=value2&field3=value3...
 *
 * The query string is composed of a series of field-value pairs.
 * Within each pair, the field name and value are separated by an equals
 * sign, '='.
 * The series of pairs is separated by the ampersand, '&' (or
 * semicolon, ';' for URLs embedded in HTML and not generated by a
 * <form>...</form>; see below).
 *
 * While there is no definitive standard, most web frameworks allow multiple
 * values to be associated with a single field
 * (e.g. field1=value1&field1=value2&field2=value3).[4][5]
 * For each field of the form, the query string contains a pair field=value.
 * Web forms may include fields that are not visible to the user; these
 * fields are included in the query string when the form is submitted
 * This convention is a W3C recommendation.[6] W3C recommends that all web
 * servers support semicolon separators in addition to ampersand
 * separators[7] to allow application/x-www-form-urlencoded query strings in
 * URLs within HTML documents without having to entity escape ampersands.
 * The form content is only encoded in the URL's query string when the form
 * submission method is GET. The same encoding is used by default when the
 * submission method is POST, but the result is submitted as the HTTP request
 * body rather than being included in a modified URL.[1]
 */
int http_decode_query_str(char * buf, unsigned int len,
						  struct httpqry_lst * qry, unsigned int max)
{
	int k;
	int v;
	int n;
	int i;
	int j;
	int c;

	n = 0;
	k = 0;
	v = 0;
	qry->buf = buf;
	for (i = 0, j = 0; i < len; i++) {
		c = buf[i];
		/* translate */
		switch (c) {
		case '+':
			buf[j++] = ' ';
			break;
		case '%':
			c = (HEX2INT(buf[i + 1]) << 4) + HEX2INT(buf[i + 2]);
			i += 2;
			buf[j++] = c;
			break;
		case '&':
		case ';':
			buf[j++] = '\0';
			if (n < max) {
				/* store the key and values string lengths */
				qry->item[n].key_len = v - k;
				qry->item[n].val_len = j - v;
				n++;
				k = j;
				v = 0;
			}
			break;
		case '=':
			buf[j++] = '\0';
			v = j;
			break;
		case '\0':
			goto done;
		case '#':
			/* FIXME: implement fragment optional part */
			break;
		default:
			buf[j++] = c;
		}
	}

done:
	buf[j] = '\0';

	if (n < max) {
		qry->item[n].key_len = v - k;
		qry->item[n].val_len = j - v;
		n++;
	}

	qry->len = n;

	return n;
}

char * http_query_lookup(struct httpctl * ctl, char * key)
{
	struct httpqry_lst * qry = &ctl->qry.lst;
	int cnt = qry->len;
	char * cp;
	int i;

	cp = qry->buf;
	for (i = 0; i < cnt; ++i) {
		char * field;
		char * val;

		field = cp;
		cp += qry->item[i].key_len;
		val = cp;
		cp += qry->item[i].val_len;

		if (strcmp(field, key) == 0)
			return val;
	}

	return NULL;
}

/* Receive content on the receiving queue */
static int http_content_enqueue(struct httpctl * ctl)
{
	uint8_t * queue = (uint8_t *)ctl->rcvq.buf;
	int cnt;
	int pos;
	int max;
	int n;

	cnt = ctl->rcvq.head;
	pos = ctl->rcvq.pos;

	/* move remaining data to the beginning of the buffer */
	n = cnt - pos;
	memcpy(queue, &queue[pos], n);
	/* the data left in the buffer is the new total count */
	cnt = n;
	/* set the search position  */
	ctl->rcvq.pos = 0;

	max = MIN(ctl->content.len, HTTP_RCVBUF_LEN);

	while (cnt < max) {
		int rem;
		/* receive more data from the network */
		rem = HTTP_RCVBUF_LEN - cnt;
		if ((n = tcp_recv(ctl->tp, &queue[cnt], rem)) <= 0) {
			tcp_close(ctl->tp);
			return n;
		}
		cnt += n;
	}

	ctl->rcvq.pos = pos;
	ctl->rcvq.head = cnt;

	return cnt;
}

int http_post(struct httpctl * ctl, const struct httpdobj * obj)
{
	int (* cgi)(struct httpctl * ctl);
	int content_type;
	int content_len;
	int len;
	int ret;

	if (obj->typ != OBJ_CODE_CGI) {
		DCC_LOG(LOG_ERROR, "invalid object type!");
		return -1;
	}

	content_type = ctl->content.type;
	content_len = ctl->content.len;

	if (content_type == APPLICATION_X_WWW_FORM_URLENCODED) {
		char *  buf;
		int n;

		DCC_LOG(LOG_TRACE, "application/x-www-form-urlencoded");

		if (content_len == 0) {
			DCC_LOG(LOG_WARNING, "zero content length!");
			n = 0;
		} else {
			if ((len = http_content_enqueue(ctl)) <= 0) {
				return len;
			}
			buf = (char *)ctl->rcvq.buf;

			n = http_decode_query_str(buf, len,
					&ctl->qry.lst, HTTP_QUERY_LST_MAX);
			if (n < 0) {
				/* FIXME: return error code */
				DCC_LOG(LOG_ERROR, "http_decode_uri_query() failed!");
				return -1;
			}
		}
	} else if (content_type == MULTIPART_FORM_DATA) {
		DCC_LOG(LOG_TRACE, "multipart/form-data");

		http_recv_queue_shift(ctl);

		if (http_multipart_boundary_lookup(ctl) < 0) {
			DCC_LOG(LOG_WARNING, "http_parse_header() failed!");
			/* Malformed request line, respond with: 400 Bad Request */
			http_400(ctl);
			tcp_close(ctl->tp);
			return -1;
		}

		http_recv_queue_shift(ctl);

		if (http_parse_header(ctl) < 0) {
			DCC_LOG(LOG_WARNING, "http_parse_header() failed!");
			/* Malformed request line, respond with: 400 Bad Request */
			http_400(ctl);
			tcp_close(ctl->tp);
			return -1;
		}

	} else {
		/* dynamic cgi */
		DCC_LOG1(LOG_TRACE, "content_type=%02x", content_type);
	}

	cgi = (int (*)(struct httpctl *))obj->ptr;
	ret = cgi(ctl);

	return ret;
}

