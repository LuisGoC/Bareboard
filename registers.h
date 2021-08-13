#ifndef _REGISTERS_H_
#define _REGISTERS_H_

#include "types.h"

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

#define GPIOA_START ((GPIOx *)0x48000000)
#define GPIOB_START ((GPIOx *)0x48000400)
#define GPIOC_START ((GPIOx *)0x48000800)
#define GPIOD_START ((GPIOx *)0x48000C00)

#define RCC_START ((RCC *)0x40021000)

#endif