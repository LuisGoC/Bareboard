#ifndef _RCC_H_
#define _RCC_H_

#include "types.h"
#include "registers.h"

#define RCC_AHBENR_GPIOA 17u //GPIOA bit position of peripheral clock enable register
#define RCC_AHBENR_GPIOB 18u //GPIOB bit position of peripheral clock enable register
#define RCC_AHBENR_GPIOC 19u //GPIOC bit position of peripheral clock enable register
#define RCC_AHBENR_GPIOD 20u //GPIOD bit position of peripheral clock enable register
#define RCC_AHBENR_GPIOF 22u //GPIOF bit position of peripheral clock enable register

#define RCC_APB2ENR_SYSCFG 0u

#define RCC_GPIOA_CLOCK_ON()    BIT_SET( RCC_START->AHBENR, RCC_AHBENR_GPIOA )
#define RCC_GPIOA_CLOCK_OFF()   BIT_RESET(RCC_START->AHBENR, RCC_AHBENR_GPIOA) //cambiar registro error
#define RCC_GPIOB_CLOCK_ON()    BIT_SET(RCC_START->AHBENR, RCC_AHBENR_GPIOB)
#define RCC_GPIOB_CLOCK_OFF()   BIT_RESET(RCC_START->AHBENR, RCC_AHBENR_GPIOB) //cambiar registro error
#define RCC_GPIOC_CLOCK_ON()    BIT_SET(RCC_START->AHBENR, RCC_AHBENR_GPIOC)
#define RCC_GPIOC_CLOCK_OFF()   BIT_RESET(RCC_START->AHBENR, RCC_AHBENR_GPIOC) //cambiar registro error
#define RCC_GPIOD_CLOCK_ON()    BIT_SET(RCC_START->AHBENR, RCC_AHBENR_GPIOD)
#define RCC_GPIOD_CLOCK_OFF()   BIT_RESET(RCC_START->AHBENR, RCC_AHBENR_GPIOD) //cambiar registro error

#define RCC_SYSCFG_CLOCK_ON()        BIT_SET( RCC_START->APB2ENR, RCC_APB2ENR_SYSCFG)
#define RCC_SYSCFG_CLOCK_OFF()       BIT_RESET( RCC_START->APB2ENR, RCC_APB2ENR_SYSCFG) //cambiar registro error


#endif