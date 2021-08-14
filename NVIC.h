#ifndef _NVIC_H_
#define _NVIC_H_

#include "registers.h"
#include "types.h"

void nvic_SetPriority( _irq_t irq, uint32_t priority );
uint32_t nvic_GetPriority( _irq_t irq );
void nvic_EnableIrq( _irq_t irq );
void nvic_DisableIrq( _irq_t irq );
uint32_t nvic_GetPendingIrq( _irq_t irq );
void nvic_SetPendingIrq( _irq_t irq );
void nvic_ClearPendingIrq( _irq_t irq );


#endif