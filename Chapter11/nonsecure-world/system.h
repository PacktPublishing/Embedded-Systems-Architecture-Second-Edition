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
#ifndef SYSTEM_H_INCLUDED
#define SYSTEM_H_INCLUDED
/* Assembly helpers */
#define DMB() __asm__ volatile ("dmb")
#define ISB() __asm__ volatile ("isb")
#define DSB() __asm__ volatile ("dsb")
#define WFI() __asm__ volatile ("wfi")


/* NVIC for TIM2 */
#define NVIC_TIM2_IRQN          (28)

/* STM32 L5 register configuration */
/*!< Memory & Instance aliases and base addresses for Non-Secure/Secure peripherals */
/*Non-Secure */
#define RCC_BASE            (0x40021000)   //RM0438 - Table 4

#define RCC_CR              (*(volatile uint32_t *)(RCC_BASE + 0x00))  //RM0438 - Table 77
#define RCC_CR_PLLRDY               (1 << 25) //RM0438 - 9.8.1
#define RCC_CR_PLLON                (1 << 24) //RM0438 - 9.8.1
#define RCC_CR_HSEBYP               (1 << 18) //RM0438 - 9.8.1
#define RCC_CR_HSERDY               (1 << 17) //RM0438 - 9.8.1
#define RCC_CR_HSEON                (1 << 16) //RM0438 - 9.8.1
#define RCC_CR_HSIRDY               (1 << 10) //RM0438 - 9.8.1
#define RCC_CR_HSION                (1 << 8)  //RM0438 - 9.8.1
#define RCC_CR_MSIRANGE_SHIFT       (4)  //RM0438 - 9.8.1
#define RCC_CR_MSIRANGE_11          (11)
#define RCC_CR_MSIRGSEL             (1 << 3)  //RM0438 - 9.8.1
#define RCC_CR_MSIPLLEN             (1 << 2)  //RM0438 - 9.8.1
#define RCC_CR_MSIRDY               (1 << 1)  //RM0438 - 9.8.1
#define RCC_CR_MSION                (1 << 0)  //RM0438 - 9.8.1

#define RCC_CFGR            (*(volatile uint32_t *)(RCC_BASE + 0x08))  //RM0438 - Table 77
/*** APB1&2 PRESCALER ***/
#define RCC_APB_PRESCALER_DIV_NONE 0x0  // 0xx: HCLK not divided
#define RCC_APB_PRESCALER_DIV_2 0x4     // 100: HCLK divided by 2
#define RCC_APB_PRESCALER_DIV_4 0x5     // 101: HCLK divided by 4
#define RCC_APB_PRESCALER_DIV_8 0x6     // 110: HCLK divided by 8
#define RCC_APB_PRESCALER_DIV_16 0x7    // 111: HCLK divided by 16

/*** AHB PRESCALER ***/
#define RCC_AHB_PRESCALER_DIV_NONE 0x0    // 0xxx: SYSCLK not divided
#define RCC_AHB_PRESCALER_DIV_2    0x8    // 1000: SYSCLK divided by 2
#define RCC_AHB_PRESCALER_DIV_4    0x9    // 1001: SYSCLK divided by 4
#define RCC_AHB_PRESCALER_DIV_8   0xA    // 1010: SYSCLK divided by 8
#define RCC_AHB_PRESCALER_DIV_16  0xB    // 1011: SYSCLK divided by 16
#define RCC_AHB_PRESCALER_DIV_64  0xC    // 1100: SYSCLK divided by 64
#define RCC_AHB_PRESCALER_DIV_128 0xD    // 1101: SYSCLK divided by 128
#define RCC_AHB_PRESCALER_DIV_256 0xE    // 1110: SYSCLK divided by 256
#define RCC_AHB_PRESCALER_DIV_512 0xF    // 1111: SYSCLK divided by 512

#define RCC_CFGR_HPRE_SHIFT        (0x04)
#define RCC_CFGR_PPRE2_SHIFT       (0x0B)
#define RCC_CFGR_PPRE1_SHIFT       (0x08)

#define RCC_CFGR_SW_MSI             0x0
#define RCC_CFGR_SW_HSI16           0x1
#define RCC_CFGR_SW_HSE             0x2
#define RCC_CFGR_SW_PLL             0x3

#define RCC_PLLCFGR         (*(volatile uint32_t *)(RCC_BASE + 0x0C))  //RM0438 - Table 77
#define RCC_PLLCFGR_PLLP_SHIFT       (27)
#define RCC_PLLCFGR_PLLR_SHIFT      (25)
#define RCC_PLLCFGR_PLLREN          (1 << 24)

#define RCC_PLLCFGR_PLLQ_SHIFT       (21)
#define RCC_PLLCFGR_PLLQEN           (1 << 20)

#define RCC_PLLCFGR_PLLN_SHIFT       (8)
#define RCC_PLLCFGR_PLLM_SHIFT       (4)

#define RCC_PLLCFGR_QR_DIV_2          0x0
#define RCC_PLLCFGR_QR_DIV_4          0x1
#define RCC_PLLCFGR_QR_DIV_6          0x2
#define RCC_PLLCFGR_QR_DIV_8          0x3

#define RCC_PLLCFGR_P_DIV_7           0x0
#define RCC_PLLCFGR_P_DIV_17          0x1

#define RCC_PLLCKSELR_PLLSRC_NONE    0x0
#define RCC_PLLCKSELR_PLLSRC_MSI     0x1
#define RCC_PLLCKSELR_PLLSRC_HSI16   0x2
#define RCC_PLLCKSELR_PLLSRC_HSE     0x3

#define RCC_APB1ENR         (*(volatile uint32_t *)(RCC_BASE + 0x58))
#define RCC_APB1ENR_PWREN         (1 << 28)

#define RCC_APB2ENR         (*(volatile uint32_t *)(RCC_BASE + 0x60))
#define RCC_APB2ENR_SYSCFGEN      (1 << 0)


/*** PWR ***/
/*!< Memory & Instance aliases and base addresses for Non-Secure/Secure peripherals */
/*Non-Secure */
#define PWR_BASE            (0x40007000)   //RM0438 - Table 4

#define PWR_CR1              (*(volatile uint32_t *)(PWR_BASE + 0x00))
#define PWR_CR1_VOS_SHIFT    (9)
#define PWR_CR1_VOS_0        (0x0)
#define PWR_CR1_VOS_1        (0x1)
#define PWR_CR1_VOS_2        (0x2)

#define PWR_CR2              (*(volatile uint32_t *)(PWR_BASE + 0x04))
#define PWR_CR2_IOSV         (1 << 9)
#define PWR_CR3              (*(volatile uint32_t *)(PWR_BASE + 0x08))
#define PWR_CR3_UCPD_DBDIS   (1 << 14)
#define PWR_CR4              (*(volatile uint32_t *)(PWR_BASE + 0x0C))

#define PWR_SR1              (*(volatile uint32_t *)(PWR_BASE + 0x10))
#define PWR_SR2              (*(volatile uint32_t *)(PWR_BASE + 0x14))
#define PWR_SR2_VOSF         (1 << 10)

#define SYSCFG_BASE          (0x40010000) //RM0438 - Table 4



/*** FLASH ***/
#define SYSCFG_APB2_CLOCK_ER_VAL    (1 << 0) //RM0438 - RCC_APB2ENR - SYSCFGEN

/*Non-Secure*/
#define FLASH_BASE          (0x40022000)   //RM0438 - Table 4
#define FLASH_KEYR        (*(volatile uint32_t *)(FLASH_BASE + 0x08))
#define FLASH_SR          (*(volatile uint32_t *)(FLASH_BASE + 0x20))
#define FLASH_CR          (*(volatile uint32_t *)(FLASH_BASE + 0x28))

/* Register values */
#define FLASH_SR_EOP                        (1 << 0)
#define FLASH_SR_OPERR                      (1 << 1)
#define FLASH_SR_PROGERR                    (1 << 3)
#define FLASH_SR_WRPERR                     (1 << 4)
#define FLASH_SR_PGAERR                     (1 << 5)
#define FLASH_SR_SIZERR                     (1 << 6)
#define FLASH_SR_PGSERR                     (1 << 7)
#define FLASH_SR_OPTWERR                    (1 << 13)
#define FLASH_SR_BSY                        (1 << 16)

#define FLASH_CR_PG                         (1 << 0)
#define FLASH_CR_PER                        (1 << 1)
#define FLASH_CR_MER1                       (1 << 2)
#define FLASH_CR_PNB_SHIFT                  3
#define FLASH_CR_PNB_MASK                   0x7F
#define FLASH_CR_BKER                       (1 << 11)
#define FLASH_CR_MER2                       (1 << 15)
#define FLASH_CR_STRT                       (1 << 16)
#define FLASH_CR_OPTSTRT                    (1 << 17)
#define FLASH_CR_EOPIE                      (1 << 24)
#define FLASH_CR_ERRIE                      (1 << 25)
#define FLASH_CR_OBL_LAUNCH                 (1 << 27)
#define FLASH_CR_OPTLOCK                    (1 << 30)
#define FLASH_CR_LOCK                       (1 << 31)

#define FLASH_ACR           (*(volatile uint32_t *)(FLASH_BASE + 0x00))
#define FLASH_ACR_LATENCY_MASK              (0x0F)

#define FLASHMEM_ADDRESS_SPACE    (0x08000000)
#define FLASH_PAGE_SIZE           (0x800) /* 2KB */
#define FLASH_BANK2_BASE          (0x08040000) /*!< Base address of Flash Bank2     */
#define FLASH_TOP                 (0x0807FFFF) /*!< FLASH end address  */

#define FLASH_KEY1                            (0x45670123)
#define FLASH_KEY2                            (0xCDEF89AB)

/* Functions defined in system.c */
void flash_set_waitstates(unsigned int waitstates);
void clock_pll_off(void);
void clock_pll_on(void);

/* NVIC */
/* NVIC ISER Base register (Cortex-M) */

#define NVIC_TIM2_IRQN          (28)
#define NVIC_ISER_BASE (0xE000E100)
#define NVIC_ICER_BASE (0xE000E180)
#define NVIC_IPRI_BASE (0xE000E400)

static inline void nvic_irq_enable(uint8_t n)
{
    int i = n / 32;
    volatile uint32_t *nvic_iser = ((volatile uint32_t *)(NVIC_ISER_BASE + 4 * i));
    *nvic_iser |= (1 << (n % 32));
}

static inline void nvic_irq_disable(uint8_t n)
{
    int i = n / 32;
    volatile uint32_t *nvic_icer = ((volatile uint32_t *)(NVIC_ICER_BASE + 4 * i));
    *nvic_icer |= (1 << (n % 32));
}

static inline void nvic_irq_setprio(uint8_t n, uint8_t prio)
{
    volatile uint8_t *nvic_ipri = ((volatile uint8_t *)(NVIC_IPRI_BASE + n));
    *nvic_ipri = prio;
}


#endif
