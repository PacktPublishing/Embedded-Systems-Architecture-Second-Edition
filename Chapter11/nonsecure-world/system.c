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
#include "system.h"

void flash_set_waitstates(unsigned int waitstates)
{
    uint32_t reg = FLASH_ACR;
    if ((reg & FLASH_ACR_LATENCY_MASK) != waitstates)
        FLASH_ACR =  (reg & ~FLASH_ACR_LATENCY_MASK) | waitstates ;
}

void clock_pll_off(void)
{
    uint32_t reg32;

     /* Select MSI as SYSCLK source. */
    reg32 = RCC_CFGR;
    reg32 &= ~((1 << 1) | (1 << 0));
    RCC_CFGR = (reg32 | RCC_CFGR_SW_MSI);
    DMB();

    /* Wait for MSI clock to be selected. */
    while ((RCC_CFGR & ((1 << 1) | (1 << 0))) != RCC_CFGR_SW_MSI) {};

    /* Turn off PLL */
    RCC_CR &= ~RCC_CR_PLLON;
    DMB();
}

void clock_pll_on(void)
{
    uint32_t reg32;
    uint32_t plln, pllm, pllq, pllp, pllr, hpre, apb1pre, apb2pre , flash_waitstates;

    RCC_APB2ENR |= RCC_APB2ENR_SYSCFGEN;
    RCC_APB1ENR |= RCC_APB1ENR_PWREN;
    PWR_CR3 |= PWR_CR3_UCPD_DBDIS;

    PWR_CR1 &= ~((1 << 10) | (1 << 9));
    PWR_CR1 |= (PWR_CR1_VOS_0 << PWR_CR1_VOS_SHIFT);
    /* Delay after setting the voltage scaling */
    reg32 = PWR_CR1;
    while ((PWR_SR2 & PWR_SR2_VOSF) != 0) {};

    while ((RCC_CR & RCC_CR_MSIRDY) == 0) {};
    flash_waitstates = 2;
    flash_set_waitstates(flash_waitstates);

    RCC_CR |= RCC_CR_MSIRGSEL;

    reg32 = RCC_CR;
    reg32 &= ~((1 << 7) | (1 << 6) | (1 << 5) | (1 << 4));
    reg32 |= (RCC_CR_MSIRANGE_11 << RCC_CR_MSIRANGE_SHIFT);
    RCC_CR = reg32;
    reg32 = RCC_CR;
    DMB();


    /* Select clock parameters (CPU Speed = 110 MHz) */
    pllm = 12;
    plln = 55;
    pllp = 7;
    pllq = RCC_PLLCFGR_QR_DIV_2;
    pllr = RCC_PLLCFGR_QR_DIV_2;
    hpre  = RCC_AHB_PRESCALER_DIV_NONE;
    apb1pre = RCC_APB_PRESCALER_DIV_NONE;
    apb2pre = RCC_APB_PRESCALER_DIV_NONE;
    flash_waitstates = 5;

    RCC_CR &= ~RCC_CR_PLLON;
    while ((RCC_CR & RCC_CR_PLLRDY) != 0) {};

    /*PLL Clock source selection*/
    reg32 = RCC_PLLCFGR ;
    reg32 |= RCC_PLLCKSELR_PLLSRC_MSI;
    reg32 |= ((pllm-1) << RCC_PLLCFGR_PLLM_SHIFT);
    reg32 |= ((plln) << RCC_PLLCFGR_PLLN_SHIFT);
    reg32 |= ((pllp) << RCC_PLLCFGR_PLLP_SHIFT);
    reg32 |= ((pllq) << RCC_PLLCFGR_PLLQ_SHIFT);
    reg32 |= ((pllr) << RCC_PLLCFGR_PLLR_SHIFT);
    RCC_PLLCFGR = reg32;
    DMB();

    RCC_CR |= RCC_CR_PLLON;
    while ((RCC_CR & RCC_CR_PLLRDY) == 0) {};

    RCC_PLLCFGR |= RCC_PLLCFGR_PLLREN;

    flash_set_waitstates(flash_waitstates);

    /*step down HPRE before going to >80MHz*/
    reg32 = RCC_CFGR ;
    reg32 &= ~((1 << 7) | (1 << 6) | (1 << 5) | (1 << 4));
    reg32 |= ((RCC_AHB_PRESCALER_DIV_2) << RCC_CFGR_HPRE_SHIFT) ;
    RCC_CFGR = reg32;
    DMB();

    /* Select PLL as SYSCLK source. */
    reg32 = RCC_CFGR;
    reg32 &= ~((1 << 1) | (1 << 0));
    RCC_CFGR = (reg32 | RCC_CFGR_SW_PLL);
    DMB();

    /* Wait for PLL clock to be selected. */
    while ((RCC_CFGR & ((1 << 1) | (1 << 0))) != RCC_CFGR_SW_PLL) {};

    /*step-up HPRE to go > 80MHz*/
    reg32 = RCC_CFGR ;
    reg32 &= ~((1 << 7) | (1 << 6) | (1 << 5) | (1 << 4));
    reg32 |= ((hpre) << RCC_CFGR_HPRE_SHIFT) ;
    RCC_CFGR = reg32;
    DMB();

    /*PRE1 and PRE2 conf*/
    reg32 = RCC_CFGR ;
    reg32 &= ~((1 << 10) | (1 << 9) | (1 << 8));
    reg32 |= ((apb1pre) << RCC_CFGR_PPRE1_SHIFT) ;
    reg32 &= ~((1 << 13) | (1 << 12) | (1 << 11));
    reg32 |= ((apb2pre) << RCC_CFGR_PPRE2_SHIFT) ;
    RCC_CFGR = reg32;

}
