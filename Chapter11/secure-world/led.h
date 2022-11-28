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
#ifndef GPIO_H_INCLUDED
#define GPIO_H_INCLUDED
#define AHB2_CLOCK_ER (*(volatile uint32_t *)(0x5002104C))
#define GPIOA_AHB2_CLOCK_ER (1 << 0)
#define GPIOB_AHB2_CLOCK_ER (1 << 1)
#define GPIOC_AHB2_CLOCK_ER (1 << 2)

#define GPIOA_BASE 0x52020000
#define GPIOB_BASE 0x52020400
#define GPIOC_BASE 0x52020800

#define GPIOA_MODE   (*(volatile uint32_t *)(GPIOA_BASE + 0x00))
#define GPIOA_OTYPE  (*(volatile uint32_t *)(GPIOA_BASE + 0x04))
#define GPIOA_OSPD   (*(volatile uint32_t *)(GPIOA_BASE + 0x08))
#define GPIOA_PUPD   (*(volatile uint32_t *)(GPIOA_BASE + 0x0c))
#define GPIOA_ODR    (*(volatile uint32_t *)(GPIOA_BASE + 0x14))
#define GPIOA_BSRR   (*(volatile uint32_t *)(GPIOA_BASE + 0x18))
#define GPIOA_AFL    (*(volatile uint32_t *)(GPIOA_BASE + 0x20))
#define GPIOA_AFH    (*(volatile uint32_t *)(GPIOA_BASE + 0x24))
#define GPIOA_SECCFG (*(volatile uint32_t *)(GPIOA_BASE + 0x30))

#define GPIOB_MODE   (*(volatile uint32_t *)(GPIOB_BASE + 0x00))
#define GPIOB_OTYPE  (*(volatile uint32_t *)(GPIOB_BASE + 0x04))
#define GPIOB_OSPD   (*(volatile uint32_t *)(GPIOB_BASE + 0x08))
#define GPIOB_PUPD   (*(volatile uint32_t *)(GPIOB_BASE + 0x0c))
#define GPIOB_ODR    (*(volatile uint32_t *)(GPIOB_BASE + 0x14))
#define GPIOB_BSRR   (*(volatile uint32_t *)(GPIOB_BASE + 0x18))
#define GPIOB_AFL    (*(volatile uint32_t *)(GPIOB_BASE + 0x20))
#define GPIOB_AFH    (*(volatile uint32_t *)(GPIOB_BASE + 0x24))
#define GPIOB_SECCFG (*(volatile uint32_t *)(GPIOB_BASE + 0x30))

#define GPIOC_MODE   (*(volatile uint32_t *)(GPIOC_BASE + 0x00))
#define GPIOC_OTYPE  (*(volatile uint32_t *)(GPIOC_BASE + 0x04))
#define GPIOC_OSPD   (*(volatile uint32_t *)(GPIOC_BASE + 0x08))
#define GPIOC_PUPD   (*(volatile uint32_t *)(GPIOC_BASE + 0x0c))
#define GPIOC_ODR    (*(volatile uint32_t *)(GPIOC_BASE + 0x14))
#define GPIOC_BSRR   (*(volatile uint32_t *)(GPIOC_BASE + 0x18))
#define GPIOC_AFL    (*(volatile uint32_t *)(GPIOC_BASE + 0x20))
#define GPIOC_AFH    (*(volatile uint32_t *)(GPIOC_BASE + 0x24))
#define GPIOC_SECCFG (*(volatile uint32_t *)(GPIOC_BASE + 0x30))


#define GREEN_LED (7) // on GPIOC
#define BLUE_LED (7)  // on GPIOB
#define RED_LED (9)   // on GPIOA

#define GPIO_OSPEED_100MHZ (0x03)
void led_setup(void);
void green_led_on(void);
void green_led_off(void);
void red_led_on(void);
void red_led_off(void);
void blue_led_on(void);
void blue_led_off(void);
void green_led_secure(int onoff);
void blue_led_secure(int onoff);
void red_led_secure(int onoff);
#endif
