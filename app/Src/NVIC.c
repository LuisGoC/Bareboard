#include "NVIC.h"
#include "registers.h"
#include "types.h"

void nvic_SetPriority( _irq_t irq, uint32_t priority )
{
    uint32_t position;
    uint8_t reg;

    position = (irq % 4) * 8;
    reg = irq/4;
    
    NVIC_START->IPR[reg] &= ~(0xFFUL << position); //clar bits
    NVIC_START->IPR[reg] |= ((priority & 3UL) << (position + 6UL)); // write bits
}

uint32_t nvic_GetPriority( _irq_t irq )
{
    uint32_t position;
    uint8_t reg;
    uint32_t priority;

    position = (irq % 4) * 8;
    reg = irq/4;
    priority = (NVIC_START->IPR[reg] >> (position + 6UL)) & 3UL;  

    return priority;
}

void nvic_EnableIrq( _irq_t irq )
{
    BIT_SET(NVIC_START->ISER, irq);
}

void nvic_DisableIrq( _irq_t irq )
{
    BIT_SET(NVIC_START->ICER, irq);
}

uint32_t nvic_GetPendingIrq( _irq_t irq )
{
    uint32_t reg;

    reg = (NVIC_START->ISPR >> irq) & 1;

    return reg;
}

void nvic_SetPendingIrq( _irq_t irq )
{
    BIT_SET(NVIC_START->ISPR, irq);
}

void nvic_ClearPendingIrq( _irq_t irq )
{
    BIT_SET(NVIC_START->ICPR, irq);
}