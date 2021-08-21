#ifndef _RCC_H_
    #define _RCC_H_

    #include "types.h"
    #include "registers.h"

    #define RCC_AHBENR_GPIOA 17u //GPIOA bit position of peripheral clock enable register
    #define RCC_AHBENR_GPIOB 18u //GPIOB bit position of peripheral clock enable register
    #define RCC_AHBENR_GPIOC 19u //GPIOC bit position of peripheral clock enable register
    #define RCC_AHBENR_GPIOD 20u //GPIOD bit position of peripheral clock enable register
    #define RCC_AHBENR_GPIOF 22u //GPIOF bit position of peripheral clock enable register

    #define RCC_APB2ENR_USART1 14u //USART1 bit position of peripheral clock enable register2
    #define RCC_APB2ENR_USART6 5u  //USART6 bit position of peripheral clock enable register2

    #define RCC_APB1ENR_USART2 17u //USART1 bit position of peripheral clock enable register
    #define RCC_APB1ENR_USART3 18u //USART1 bit position of peripheral clock enable register
    #define RCC_APB1ENR_USART4 19u //USART1 bit position of peripheral clock enable register
    #define RCC_APB1ENR_USART5 20u //USART1 bit position of peripheral clock enable register


    #define RCC_APB2ENR_SYSCFG 0u

    #define RCC_GPIOA_CLOCK_ON()         BIT_SET( RCC_START->AHBENR, RCC_AHBENR_GPIOA )
    #define RCC_GPIOA_CLOCK_OFF()        BIT_RESET(RCC_START->AHBENR, RCC_AHBENR_GPIOA) 
    #define RCC_GPIOB_CLOCK_ON()         BIT_SET(RCC_START->AHBENR, RCC_AHBENR_GPIOB)
    #define RCC_GPIOB_CLOCK_OFF()        BIT_RESET(RCC_START->AHBENR, RCC_AHBENR_GPIOB) 
    #define RCC_GPIOC_CLOCK_ON()         BIT_SET(RCC_START->AHBENR, RCC_AHBENR_GPIOC)
    #define RCC_GPIOC_CLOCK_OFF()        BIT_RESET(RCC_START->AHBENR, RCC_AHBENR_GPIOC) 
    #define RCC_GPIOD_CLOCK_ON()         BIT_SET(RCC_START->AHBENR, RCC_AHBENR_GPIOD)
    #define RCC_GPIOD_CLOCK_OFF()        BIT_RESET(RCC_START->AHBENR, RCC_AHBENR_GPIOD) 

    #define RCC_SYSCFG_CLOCK_ON()        BIT_SET( RCC_START->APB2ENR, RCC_APB2ENR_SYSCFG)
    #define RCC_SYSCFG_CLOCK_OFF()       BIT_RESET( RCC_START->APB2ENR, RCC_APB2ENR_SYSCFG) 

    #define RCC_USART1_CLOCK_ON()        BIT_SET( RCC_START->APB2ENR, RCC_APB2ENR_USART1) 
    #define RCC_USART1_CLOCK_OFF()       BIT_RESET( RCC_START->APB2ENR, RCC_APB2ENR_USART1) 
    #define RCC_USART6_CLOCK_ON()        BIT_SET( RCC_START->APB2ENR, RCC_APB2ENR_USART6) 
    #define RCC_USART6_CLOCK_OFF()       BIT_RESET( RCC_START->APB2ENR, RCC_APB2ENR_USART6) 

    #define RCC_USART2_CLOCK_ON()        BIT_SET( RCC_START->APB1ENR, RCC_APB1ENR_USART2) 
    #define RCC_USART2_CLOCK_OFF()       BIT_RESET( RCC_START->APB1ENR, RCC_APB1ENR_USART2) 
    #define RCC_USART3_CLOCK_ON()        BIT_SET( RCC_START->APB1ENR, RCC_APB1ENR_USART3) 
    #define RCC_USART3_CLOCK_OFF()       BIT_RESET( RCC_START->APB1ENR, RCC_APB1ENR_USART3) 
    #define RCC_USART4_CLOCK_ON()        BIT_SET( RCC_START->APB1ENR, RCC_APB1ENR_USART4) 
    #define RCC_USART4_CLOCK_OFF()       BIT_RESET( RCC_START->APB1ENR, RCC_APB1ENR_USART4) 
    #define RCC_USART5_CLOCK_ON()        BIT_SET( RCC_START->APB1ENR, RCC_APB1ENR_USART5) 
    #define RCC_USART5_CLOCK_OFF()       BIT_RESET( RCC_START->APB1ENR, RCC_APB1ENR_USART5) 


#endif