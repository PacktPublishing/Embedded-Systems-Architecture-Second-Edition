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
#define BLUE_LED_PIN (15)
#define RED_LED_PIN (14)
#define ORANGE_LED_PIN (13)
#define GREEN_LED_PIN (12)

void led_setup(void);
void led_on(int pin);
void led_off(int pin);
void led_toggle(int pin);

#define blue_led_on() led_on(BLUE_LED_PIN)
#define blue_led_off() led_off(BLUE_LED_PIN)
#define blue_led_toggle() led_toggle(BLUE_LED_PIN)

#define red_led_on() led_on(RED_LED_PIN)
#define red_led_off() led_off(RED_LED_PIN)
#define red_led_toggle() led_toggle(RED_LED_PIN)

#define orange_led_on() led_on(ORANGE_LED_PIN)
#define orange_led_off() led_off(ORANGE_LED_PIN)
#define orange_led_toggle() led_toggle(ORANGE_LED_PIN)

#define green_led_on() led_on(GREEN_LED_PIN)
#define green_led_off() led_off(GREEN_LED_PIN)
#define green_led_toggle() led_toggle(GREEN_LED_PIN)
#endif
