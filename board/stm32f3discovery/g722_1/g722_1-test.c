/* 
 * Copyright(C) 2012 Robinson Mittmann. All Rights Reserved.
 * 
 * This file is part of the YARD-ICE.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 3.0 of the License, or (at your option) any later version.
 * 
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 * 
 * You can receive a copy of the GNU Lesser General Public License from 
 * http://www.gnu.org/
 */

/** 
 * @file g722_1-test.c
 * @brief G722.1 codec test
 * @author Robinson Mittmann <bobmittmann@gmail.com>
 */ 

#include <sys/stm32f.h>
#include <sys/console.h>
#include <stdio.h>
#include <stdlib.h>
#include <thinkos.h>

#include "board.h"

/* GPIO pin description */ 
struct stm32f_io {
	struct stm32_gpio * gpio;
	uint8_t pin;
};

/* ----------------------------------------------------------------------
 * LEDs 
 * ----------------------------------------------------------------------
 */

const struct stm32f_io led_io[] = {
	{ LED3_IO }, /* LED3 */
	{ LED5_IO }, /* LED5 */
	{ LED7_IO }, /* LED7 */
	{ LED9_IO }, /* LED9 */
	{ LED10_IO }, /* LED10 */
	{ LED8_IO }, /* LED8 */
	{ LED6_IO }, /* LED6 */
	{ LED4_IO }, /* LED4 */
};

#define LED_COUNT (sizeof(led_io) / sizeof(struct stm32f_io))

void led_on(unsigned int id)
{
	__led_on(led_io[id].gpio, led_io[id].pin);
}

void led_off(unsigned int id)
{
	__led_off(led_io[id].gpio, led_io[id].pin);
}

void led_toggle(unsigned int id)
{
	__led_toggle(led_io[id].gpio, led_io[id].pin);
}

#include <g722_1.h>

g722_1_encode_state_t encode_state;
int16_t amp[MAX_FRAME_SIZE];
uint8_t g722_1_code[MAX_BITS_PER_FRAME/8];

int encode_test(void)
{
    g722_1_encode_state_t *s;
    int samples;

    if ((s = g722_1_encode_init(&encode_state, G722_1_SAMPLE_RATE_32000, 
								G722_1_BIT_RATE_32000 )) == NULL) {
		return -1;
    }

    for (;;) {
        samples = 64;
        g722_1_encode(s, g722_1_code, amp, samples);
    }

    return 0;
}
int main(int argc, char ** argv)
{
	int i;

	for (i = 0; ; ++i) {
		led_off((i - 2) & 0x7);
		led_on(i & 0x7);
		/* wait 100 ms */
		thinkos_sleep(100);

		encode_test();
	}

	return 0;
}

