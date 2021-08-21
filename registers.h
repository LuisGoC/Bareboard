#ifndef _REGISTERS_H_
     #define _REGISTERS_H_

     #include "types.h"

     typedef enum{
          WWDG_IRQn, 
          RTC_IRQn = 2, 
          FLASH_IRQn, 
          RCC_IRQn, 
          EXTI0_1_IRQn, 
          EXTI2_3_IRQn, 
          EXTI4_15_IRQn, 
          DMA_CH1_IRQn = 9, 
          DMA_CH2_3_IRQn, 
          DMA_CH4_5_IRQn,
          ADC_IRQn,
          TIM1_BRK_UP_TRG_COM_IRQn,
          TIM1_CC_IRQn,
          TIM3_IRQn = 16,
          TIM6_IRQn,
          TIM7_IRQn,
          TIM14_IRQn,
          TIM15_IRQn,
          TIM16_IRQn,
          TIM17_IRQn,
          I2C1_IRQn,
          I2C2_IRQn,
          SPI1_IRQn,
          SPI2_IRQn,
          USART1_IRQn,
          USART2_IRQn,
          USART3_4_5_6_IRQn,
          USB_IRQn = 31
     }_irq_t;

     typedef struct {
          uint32_t MODER;
          uint32_t OTYPER;
          uint32_t OSPEEDR;
          uint32_t PUPDR;
          uint32_t IDR;
          uint32_t ODR;
          uint32_t BSRR;
          uint32_t LCKR;
          uint32_t AFRL;
          uint32_t AFRH;
          uint32_t BRR;
     }GPIOx;

     typedef struct {
          uint32_t CR1;
          uint32_t CR2;
          uint32_t CR3;
          uint32_t BRR;
          uint32_t reserved;
          uint32_t RTOR;
          uint32_t RQR;
          uint32_t ISR;
          uint32_t ICR;
          uint32_t RDR;
          uint32_t TDR;
     }USARTx;

     typedef struct {
          uint32_t CR;
          uint32_t CFGR;
          uint32_t CIR;
          uint32_t APB2RSTR;
          uint32_t APB1RSTR;
          uint32_t AHBENR;
          uint32_t APB2ENR;
          uint32_t APB1ENR;
          uint32_t BDCR;
          uint32_t CSR;
          uint32_t AHBRSTR;
          uint32_t CFGR2;
          uint32_t CFGR3;
          uint32_t CR2;
     }RCC;

     typedef struct {
          uint32_t ISER;
          uint32_t reserved_0[31];
          uint32_t ICER;
          uint32_t reserved_1[31];
          uint32_t ISPR;
          uint32_t reserved_2[31];
          uint32_t ICPR;
          uint32_t reserved_3[95];
          uint32_t IPR[7];
     }NVIC;

     typedef struct {
          uint32_t IMR;
          uint32_t EMR;
          uint32_t RTSR;
          uint32_t FTSR;
          uint32_t SWIER;
          uint32_t PR;
     }EXTI;

     typedef struct {
          uint32_t CFGR1;
          uint32_t reserved;
          uint32_t EXTICR[4];
          uint32_t CFGR2;
     }SYSCFG;

     #define GPIOA_START ((GPIOx *)0x48000000)
     #define GPIOB_START ((GPIOx *)0x48000400)
     #define GPIOC_START ((GPIOx *)0x48000800)
     #define GPIOD_START ((GPIOx *)0x48000C00)

     #define USART1_START ((USARTx *)0x40013800)
     #define USART2_START ((USARTx *)0x40004400)
     #define USART3_START ((USARTx *)0x40004800)
     #define USART4_START ((USARTx *)0x40004C00)
     #define USART5_START ((USARTx *)0x40005000)
     #define USART6_START ((USARTx *)0x40011400)

     #define RCC_START   ((RCC *)0x40021000)

     #define NVIC_START ((NVIC *)0xE000E100)

     #define EXTI_START ((EXTI *)0x40010400)

     #define SYSCFG_START ((SYSCFG *)0x40010000)

#endif