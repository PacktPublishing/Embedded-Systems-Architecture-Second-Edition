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
#include <stdlib.h>
#include "system.h"
#include "button.h"

#define AHB1_CLOCK_ER (*(volatile uint32_t *)(0x40023830))
#define GPIOA_AHB1_CLOCK_ER (1 << 0)

#define GPIOA_BASE 0x40020000
#define GPIOA_MODE (*(volatile uint32_t *)(GPIOA_BASE + 0x00))
#define GPIOA_IDR  (*(volatile uint32_t *)(GPIOA_BASE + 0x10))
#define BUTTON_PIN (0)

#define EXTI_CR_BASE (0x40013808)
#define EXTI_CR0 (*(volatile uint32_t *)(EXTI_CR_BASE + 0x00))
#define EXTI_CR_EXTI0_MASK (0xFFFF)

#define EXTI_BASE (0x40013C00)
#define EXTI_IMR    (*(volatile uint32_t *)(EXTI_BASE + 0x00))
#define EXTI_EMR    (*(volatile uint32_t *)(EXTI_BASE + 0x04))
#define EXTI_RTSR   (*(volatile uint32_t *)(EXTI_BASE + 0x08))
#define EXTI_FTSR   (*(volatile uint32_t *)(EXTI_BASE + 0x0c))
#define EXTI_SWIER  (*(volatile uint32_t *)(EXTI_BASE + 0x10))
#define EXTI_PR     (*(volatile uint32_t *)(EXTI_BASE + 0x14))

static void (*button_callback)(void) = NULL;

void button_setup(void (*callback)(void))
{
    AHB1_CLOCK_ER |= GPIOA_AHB1_CLOCK_ER;

    GPIOA_MODE &= ~ (0x03 << (BUTTON_PIN * 2));
    EXTI_CR0 &= ~EXTI_CR_EXTI0_MASK;
    
    button_callback = callback;
}

void button_start_read(void)
{
    EXTI_IMR |= (1 << BUTTON_PIN);
    EXTI_EMR |= (1 << BUTTON_PIN);
    EXTI_RTSR |= (1 << BUTTON_PIN);
    nvic_irq_enable(NVIC_EXTI0_IRQN);
}

void isr_exti0(void)
{
    nvic_irq_disable(NVIC_EXTI0_IRQN);
    EXTI_PR |= (1 << BUTTON_PIN);
    if (button_callback)
        button_callback();
}

