/*
 *
 * Embedded System Architecture - Second Edition
 * Copyright (c) 2018-2022 Packt
 *
 * Author: Daniele Lacamera <root@danielinux.net>
 *
 * MIT License
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal 
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, 
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE 
 * SOFTWARE.
 */
#include <stdint.h>
#include "led.h"

/* Application's Vector offset register, non-secure */
#define VTOR_NS (*(volatile uint32_t *)(0xE002ED08))

/* Entry point for the non-secure world */
#define NS_WORLD_ENTRY_ADDRESS (0x08040000)

#define SCB_SHCSR     (*(volatile uint32_t *)(0xE000ED24))
#define SCB_SHCSR_SECUREFAULT_EN            (1<<19)



/* SAU registers, used to define memory mapped regions */
#define SAU_CTRL   (*(volatile uint32_t *)(0xE000EDD0))
#define SAU_RNR (*(volatile uint32_t *)(0xE000EDD8)) /** SAU_RNR - region number register **/
#define SAU_RBAR (*(volatile uint32_t *)(0xE000EDDC)) /** SAU_RBAR - region base address register **/
#define SAU_RLAR (*(volatile uint32_t *)(0xE000EDE0)) /** SAU_RLAR - region limit address register **/

#define SAU_REGION_MASK 0x000000FF 
#define SAU_ADDR_MASK 0xFFFFFFE0 /* LS 5 bit are reserved or used for flags */

/* Flag for the SAU region limit register */
#define SAU_REG_ENABLE (1 << 0) /* Indicates that the region is enabled. */
#define SAU_REG_SECURE (1 << 1) /* When on, the region is S or NSC */

#define SAU_INIT_CTRL_ENABLE (1 << 0)
#define SAU_INIT_CTRL_ALLNS  (1 << 1)

static void sau_init_region(uint32_t region, uint32_t start_addr,
        uint32_t end_addr, int secure)
{
    uint32_t secure_flag = 0;
    if (secure)
        secure_flag = SAU_REG_SECURE;
    SAU_RNR = region & SAU_REGION_MASK;
    SAU_RBAR = start_addr & SAU_ADDR_MASK;
    SAU_RLAR = (end_addr & SAU_ADDR_MASK)
        | secure_flag | SAU_REG_ENABLE;
}


static void secure_world_init(void)
{
    /* Non-secure callable: NSC functions area */
    sau_init_region(0, 0x0C001000, 0x0C001FFF, 1);

    /* Non-secure: application flash area */
    sau_init_region(1, 0x08040000, 0x0804FFFF, 0);
    
    /* Non-secure RAM region in SRAM1 */
    sau_init_region(2, 0x20018000, 0x2002FFFF, 0);

    /* Non-secure: internal peripherals */
    sau_init_region(3, 0x40000000, 0x4FFFFFFF, 0);

    /* Enable SAU */
    SAU_CTRL = SAU_INIT_CTRL_ENABLE;

    /* Enable securefault handler */
    SCB_SHCSR |= SCB_SHCSR_SECUREFAULT_EN;

}

#define GTZC_MPCBB1_S_BASE        (0x50032C00)
#define GTZC_MPCBB1_S_VCTR_BASE   (GTZC_MPCBB1_S_BASE + 0x100)

#define GTZC_MPCBB2_S_BASE        (0x50033000)
#define GTZC_MPCBB2_S_VCTR_BASE   (GTZC_MPCBB2_S_BASE + 0x100)

#define SET_GTZC_MPCBBx_S_VCTR(bank,n,val) \
    (*((volatile uint32_t *)(GTZC_MPCBB##bank##_S_VCTR_BASE ) + n ))= val

static void gtzc_init(void)
{
   int i;
  /* Configure lower half of SRAM1 as secure */
   for (i = 0; i < 12; i++) {
       SET_GTZC_MPCBBx_S_VCTR(1, i, 0xFFFFFFFF);
   } 
   /* Configure upper half of SRAM1 as non-secure */
   for (i = 12; i < 24; i++) {
       SET_GTZC_MPCBBx_S_VCTR(1, i, 0x0);
   } 

  /* Configure SRAM2 as secure */
   for (i = 0; i < 8; i++) {
       SET_GTZC_MPCBBx_S_VCTR(2, i, 0xFFFFFFFF);
   } 
}



/* This is the main program loop for the bootloader.
 *
 * It performs the following actions:
 *  - Initialize SAU
 *  - Initialize GTZC
 *  - update the Interrupt Vector NS offset using the address of the app
 *  - Set the initial stack pointer and the offset of the app
 *  - Change the stack pointer
 *  - Call the application entry point via bxns
 *
 */

void main(void) 
{
    const uint32_t * const app_IV = (const uint32_t *)NS_WORLD_ENTRY_ADDRESS;
    void  *app_entry;
    uint32_t app_end_stack;
    volatile int i;
    led_setup();
    red_led_on();

    /* Update IV */
    VTOR_NS = ((uint32_t)app_IV);

    /* Initialize SAU and GTZC */
    secure_world_init();
    gtzc_init();

    /* Read stack pointer, entry point before securing flash area */
    app_end_stack = (*((uint32_t *)(NS_WORLD_ENTRY_ADDRESS)));
    app_entry = (void *)(*((uint32_t *)(NS_WORLD_ENTRY_ADDRESS + 4)));

    for (i = 0; i < 1100000; i++)
        asm volatile("NOP");
    red_led_off();

    red_led_secure(1);
    green_led_secure(0);
    blue_led_secure(1);


    /* Update stack pointer */
    asm volatile("msr msplim, %0" ::"r"(0));
    asm volatile("msr msp_ns, %0" ::"r"(app_end_stack));
    /* Jump to non secure app_entry */
    asm volatile("mov r12, %0" ::"r"(app_entry));
    asm volatile("bic.w   r12, r12, #1");
    asm volatile("blxns   r12" );

}
