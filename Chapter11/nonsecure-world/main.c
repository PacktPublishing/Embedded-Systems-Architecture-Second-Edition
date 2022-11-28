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
#include <stdlib.h>
#include <stdint.h>
#include "system.h"
#include "timer.h"
#include "led.h"
#define CPU_FREQ (110 * 1000 * 1000)

void nsc_blue_led_toggle(void);

void main(void) {
    int i;
    clock_pll_on();
    led_setup();

    /* Green LED is non-secure: we can turn it on */
    green_led_on();

    /* Blue and Red LEDs are secure. The following
     * will silently fail:
     */
    blue_led_on();
    red_led_on();

    while(1) {

        /*
         * Call the veneer for controlling a secure LED
         */
        nsc_blue_led_toggle();

        for (i = 0; i < 800000; i++)
            asm volatile ("NOP");
    }
}


