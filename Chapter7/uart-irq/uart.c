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
#include <string.h>
#include "uart.h"
#include "system.h"

#define UART3 (0x40004800)

#define UART3_SR       (*(volatile uint32_t *)(UART3))
#define UART3_DR       (*(volatile uint32_t *)(UART3 + 0x04))
#define UART3_BRR      (*(volatile uint32_t *)(UART3 + 0x08))
#define UART3_CR1      (*(volatile uint32_t *)(UART3 + 0x0c))
#define UART3_CR2      (*(volatile uint32_t *)(UART3 + 0x10))

#define UART_CR1_UART_ENABLE    (1 << 13)
#define UART_CR1_SYMBOL_LEN     (1 << 12)
#define UART_CR1_PARITY_ENABLED (1 << 10)
#define UART_CR1_PARITY_ODD     (1 << 9)
#define UART_CR1_TXEIE          (1 << 7)
#define UART_CR1_RXNEIE         (1 << 5)
#define UART_CR1_TX_ENABLE      (1 << 3)
#define UART_CR1_RX_ENABLE      (1 << 2)
#define UART_CR2_STOPBITS       (3 << 12)
#define UART_SR_TX_EMPTY        (1 << 7)
#define UART_SR_RX_NOTEMPTY     (1 << 5)


#define CLOCK_SPEED (168000000)
#define NVIC_UART3_IRQN          (39)

#define APB1_CLOCK_ER           (*(volatile uint32_t *)(0x40023840))
#define UART3_APB1_CLOCK_ER_VAL 	(1 << 18)

#define AHB1_CLOCK_ER (*(volatile uint32_t *)(0x40023830))
#define GPIOD_AHB1_CLOCK_ER (1 << 3)
#define GPIOD_BASE 0x40020c00
#define GPIOD_MODE  (*(volatile uint32_t *)(GPIOD_BASE + 0x00))
#define GPIOD_AFL   (*(volatile uint32_t *)(GPIOD_BASE + 0x20))
#define GPIOD_AFH   (*(volatile uint32_t *)(GPIOD_BASE + 0x24))
#define GPIO_MODE_AF (2)
#define UART3_PIN_AF 7
#define UART3_RX_PIN 9
#define UART3_TX_PIN 8

static void uart3_tx_interrupt_onoff(int enable)
{
    if (enable)
    	UART3_CR1 |= UART_CR1_TXEIE;
    else
    	UART3_CR1 &= ~UART_CR1_TXEIE;
}

static void uart3_rx_interrupt_onoff(int enable)
{
    if (enable)
    	UART3_CR1 |= UART_CR1_RXNEIE;
    else
    	UART3_CR1 &= ~UART_CR1_RXNEIE;
}


static void uart3_pins_setup(void)
{
    AHB1_CLOCK_ER |= GPIOD_AHB1_CLOCK_ER;
    uint32_t reg;
    /* Set mode = AF */
    reg = GPIOD_MODE & ~ (0x03 << (UART3_RX_PIN * 2));
    GPIOD_MODE = reg | (2 << (UART3_RX_PIN * 2));
    reg = GPIOD_MODE & ~ (0x03 << (UART3_TX_PIN * 2));
    GPIOD_MODE = reg | (2 << (UART3_TX_PIN * 2));

    /* Alternate function: use high pins (8 and 9) */
    reg = GPIOD_AFH & ~(0xf << ((UART3_TX_PIN - 8) * 4));
    GPIOD_AFH = reg | (UART3_PIN_AF << ((UART3_TX_PIN - 8) * 4));
    reg = GPIOD_AFH & ~(0xf << ((UART3_RX_PIN - 8) * 4));
    GPIOD_AFH = reg | (UART3_PIN_AF << ((UART3_RX_PIN - 8) * 4));
}

int uart3_setup(uint32_t bitrate, uint8_t data, char parity, uint8_t stop)
{
    uint32_t reg;
    /* Enable pins and configure for AF7 */
    uart3_pins_setup();
    /* Turn on the device */
    APB1_CLOCK_ER |= UART3_APB1_CLOCK_ER_VAL;

    /* Configure for TX + RX */
    UART3_CR1 |= (UART_CR1_TX_ENABLE | UART_CR1_RX_ENABLE);

    /* Configure clock */
    UART3_BRR =  CLOCK_SPEED / bitrate;

    /* Configure data bits */
    if (data == 8)
        UART3_CR1 &= ~UART_CR1_SYMBOL_LEN;
    else
        UART3_CR1 |= UART_CR1_SYMBOL_LEN;

    /* Default: No parity */
    UART3_CR1 &= ~(UART_CR1_PARITY_ENABLED | UART_CR1_PARITY_ODD);

    /* Configure parity */
    switch (parity) {
        case 'O':
            UART3_CR1 |= UART_CR1_PARITY_ODD;
            /* fall through to enable parity */
        case 'E':
            UART3_CR1 |= UART_CR1_PARITY_ENABLED;
            break;
    }

    /* Set stop bits */
    reg = UART3_CR2 & ~UART_CR2_STOPBITS;
    if (stop > 1)
        UART3_CR2 = reg & (2 << 12);
    else
        UART3_CR2 = reg;

    /* Enable interrupts in NVIC */
    nvic_irq_enable(NVIC_UART3_IRQN);
    nvic_irq_setprio(NVIC_UART3_IRQN, 0);

    /* Enable RX interrupt */
    uart3_rx_interrupt_onoff(1);

    /* Turn on uart */
    UART3_CR1 |= UART_CR1_UART_ENABLE;

    return 0;
}


static char buf_rx[64];
static int received_bytes = 0;

static char buf_tx[64];
static int tx_pending_bytes = 0, tx_transmitted_bytes = 0;

void isr_uart3(void)
{
    volatile uint32_t reg;
    reg = UART3_SR;
    if (reg & UART_SR_RX_NOTEMPTY) {
        if (received_bytes >= 64)
            reg = UART3_DR;
        else
            buf_rx[received_bytes++] = (char)(UART3_DR & 0xFF);
    }

    if ((reg & UART_SR_TX_EMPTY) &&
            (tx_pending_bytes > tx_transmitted_bytes)) {
        UART3_DR = buf_tx[tx_transmitted_bytes++];
        if (tx_transmitted_bytes == tx_pending_bytes) {
            uart3_tx_interrupt_onoff(0);
            tx_transmitted_bytes = tx_pending_bytes = 0;
        }
    }
}


void uart3_write(const char *text)
{
    const char *p = text;
    int i;
    volatile uint32_t reg;
    while(*p) {
        reg = UART3_SR;
        if (reg & UART_SR_TX_EMPTY)
        {
            UART3_DR = *p;
        } else {
            if (tx_pending_bytes >= 63)
                break;
            buf_tx[tx_pending_bytes++] = *p;
            uart3_tx_interrupt_onoff(1);
        }
        p++;
    }
}

int uart3_read(char *buf, int len)
{
    int ret = 0;
    if (received_bytes < len)
        len = received_bytes;
    if (received_bytes > 0) {
        int i;
        for (i = 0; i < len; i++)
            buf[i] = buf_rx[i];
        ret = len;
        received_bytes = 0;
    }
    return ret;
}
