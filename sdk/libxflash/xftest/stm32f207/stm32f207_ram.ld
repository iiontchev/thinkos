/* 
 * stm32f103x6.ld
 *
 * Copyright(C) 2013 Robinson Mittmann. All Rights Reserved.
 * 
 * This file is part of the ThinkOS library.
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

/* 
   Medium-density performance line ARM-based 32-bit MCU with 64
   or 128 KB Flash, USB, CAN, 7 timers, 2 ADCs, 9 com. interfaces
*/

OUTPUT_FORMAT ("elf32-littlearm")
ENTRY(_reset)
SEARCH_DIR(.)

MEMORY
{
	vectors(r) : ORIGIN = 0x00000000, LENGTH = 1K
	flash (rx) : ORIGIN = 0x08000000, LENGTH = 512K
	sram  (rw) : ORIGIN = 0x20000000, LENGTH = 128K
	dcclog (r) : ORIGIN = 0x40000000, LENGTH = 1024K
}

_stack = ORIGIN(sram) + LENGTH(sram);

EXTERN(_stack)
EXTERN(_reset)

EXTERN(cm3_nmi_isr)
EXTERN(cm3_hard_fault_isr)
EXTERN(cm3_mem_manage_isr)
EXTERN(cm3_bus_fault_isr)
EXTERN(cm3_usage_fault_isr)
EXTERN(cm3_svc_isr)
EXTERN(cm3_debug_mon_isr)
EXTERN(cm3_pendsv_isr)
EXTERN(cm3_systick_isr)
EXTERN(stm32f_wwdg_isr)
EXTERN(stm32f_pvd_isr)
EXTERN(stm32f_tamp_stamp_isr)
EXTERN(stm32f_rtc_wkup_isr)
EXTERN(stm32f_flash_isr)
EXTERN(stm32f_rcc_isr)
EXTERN(stm32f_exti0_isr)
EXTERN(stm32f_exti1_isr)
EXTERN(stm32f_exti2_isr)
EXTERN(stm32f_exti3_isr)
EXTERN(stm32f_exti4_isr)
EXTERN(stm32f_dma1_stream0_isr)
EXTERN(stm32f_dma1_stream1_isr)
EXTERN(stm32f_dma1_stream2_isr)
EXTERN(stm32f_dma1_stream3_isr)
EXTERN(stm32f_dma1_stream4_isr)
EXTERN(stm32f_dma1_stream5_isr)
EXTERN(stm32f_dma1_stream6_isr)
EXTERN(stm32f_adc_isr)
EXTERN(stm32f_can1_tx_isr)
EXTERN(stm32f_can1_rx0_isr)
EXTERN(stm32f_can1_rx1_isr)
EXTERN(stm32f_can1_sce_isr)
EXTERN(stm32f_exti9_5_isr)
EXTERN(stm32f_tim1_brk_tim9_isr)
EXTERN(stm32f_tim1_up_tim10_isr)
EXTERN(stm32f_tim1_trg_com_tim11_isr)
EXTERN(stm32f_tim1_cc_isr)
EXTERN(stm32f_tim2_isr)
EXTERN(stm32f_tim3_isr)
EXTERN(stm32f_tim4_isr)
EXTERN(stm32f_i2c1_ev_isr)
EXTERN(stm32f_i2c1_er_isr)
EXTERN(stm32f_i2c2_ev_isr)
EXTERN(stm32f_i2c2_er_isr)
EXTERN(stm32f_spi1_isr)
EXTERN(stm32f_spi2_isr)
EXTERN(stm32f_usart1_isr)
EXTERN(stm32f_usart2_isr)
EXTERN(stm32f_usart3_isr)
EXTERN(stm32f_exti15_10_isr)
EXTERN(stm32f_rtc_alarm_isr)
EXTERN(stm32f_otg_fs_wkup_isr)
EXTERN(stm32f_tim8_brk_tim12_isr)
EXTERN(stm32f_tim8_up_tim13_isr)
EXTERN(stm32f_tim8_trg_com_tim14_isr)
EXTERN(stm32f_tim8_cc_isr)
EXTERN(stm32f_dma1_stream7_isr)
EXTERN(stm32f_fsmc_isr)
EXTERN(stm32f_sdio_isr)
EXTERN(stm32f_tim5_isr)
EXTERN(stm32f_spi3_isr)
EXTERN(stm32f_uart4_isr)
EXTERN(stm32f_uart5_isr)
EXTERN(stm32f_tim6_dac_isr)
EXTERN(stm32f_tim7_isr)
EXTERN(stm32f_dma2_stream0_isr)
EXTERN(stm32f_dma2_stream1_isr)
EXTERN(stm32f_dma2_stream2_isr)
EXTERN(stm32f_dma2_stream3_isr)
EXTERN(stm32f_dma2_stream4_isr)
EXTERN(stm32f_eth_isr)
EXTERN(stm32f_eth_wkup_isr)
EXTERN(stm32f_can2_tx_isr)
EXTERN(stm32f_can2_rx0_isr)
EXTERN(stm32f_can2_rx1_isr)
EXTERN(stm32f_can2_sce_isr)
EXTERN(stm32f_otg_fs_isr)
EXTERN(stm32f_dma2_stream5_isr)
EXTERN(stm32f_dma2_stream6_isr)
EXTERN(stm32f_dma2_stream7_isr)
EXTERN(stm32f_usart6_isr)
EXTERN(stm32f_i2c3_ev_isr)
EXTERN(stm32f_i2c3_er_isr)
EXTERN(stm32f_otg_hs_ep1_out_isr)
EXTERN(stm32f_otg_hs_ep1_in_isr)
EXTERN(stm32f_otg_hs_wkup_isr)
EXTERN(stm32f_otg_hs_isr)
EXTERN(stm32f_dcmi_isr)
EXTERN(stm32f_cryp_isr)
EXTERN(stm32f_hash_rng_isr)
EXTERN(stm32f_fpu_isr)
EXTERN(stm32f_uart7_isr)
EXTERN(stm32f_uart8_isr)
EXTERN(stm32f_spi4_isr)
EXTERN(stm32f_spi5_isr)
EXTERN(stm32f_spi6_isr)
EXTERN(stm32f_sai1_isr)
EXTERN(stm32f_lcd_isr)
EXTERN(stm32f_lcd_err_isr)
EXTERN(stm32f_dma2d_isr)

SECTIONS
{
	. = 0;

	.dcclog :
	{
		. = ALIGN(4);
		KEEP(*(.dcclog))
	} >dcclog

	.dccdata :
	{
		. = ALIGN(4);
		KEEP(*(.rodata.__FUNCTION__*))
		KEEP(*(.dccdata))
	} >dcclog

	.init :
	{
		KEEP (*(.rom_vectors))
		KEEP (*(.boot))
		KEEP (*(.init))
		/* define a global symbol marking the end of read only data sections */
		. = ALIGN(8); 
		PROVIDE(__text_end = .);
	} >flash = 0xffffffff

	.text :
	{
		. = ALIGN(4);
		/* create a global symbol marking the start of the .data section  */
		PROVIDE (__data_start = . );
		KEEP (*(.ram_vectors))
		/* all .text sections (code)  */
		*(.text .text.* .gnu.linkonce.t.*)
		/* all .glue_7t sections (interworking thumb helpers) */
		*(.glue_7) *(.glue_7t) *(.vfp11_veneer) *(.v4_bx)
		/* all .rodata sections (constants, strings, etc.)  */
		*(.rodata .rodata.* .gnu.linkonce.r.*)
		. = ALIGN(4);
		/* constructors */
		PROVIDE(__ctors_start = .);
		KEEP (*(SORT(.init_array.*))) /* gcc 4.6 */
		KEEP (*(.init_array))
		KEEP(*(SORT(.ctors.*)))
		KEEP(*(.ctors))
		PROVIDE(__ctors_end = .);
	} >sram AT >flash = 0xffffffff

	.data :
	{
		/* all .data sections  */
		*(.data .data*)
		/* define a global symbol marking the end of the .data section  */
		. = ALIGN(4);
		PROVIDE (__data_end = . );
	} >sram AT >flash

	PROVIDE(__image_size = SIZEOF(.init) + SIZEOF(.text) + SIZEOF(.data));

	.bss :
	{
		/* define a global symbol marking the start of the .bss section */
		PROVIDE (__bss_start = . );
		/* all .bss sections  */
		*(.bss .bss*)
	} >sram

	/* advance location counter to the next 32-bit boundary */
	. = ALIGN(4);
	PROVIDE (__bss_end = . );

	.heap :
	{
		PROVIDE (__heap_start = . );
		/* all .heap sections  */
		*(.heap .heap*)
	} >sram

	/* advance location counter to the next 32-bit boundary */
	. = ALIGN(4);
	PROVIDE (__heap_base = . );
}

