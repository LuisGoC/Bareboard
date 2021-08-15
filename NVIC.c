#include "NVIC.h"
#include "registers.h"
#include "types.h"

void nvic_SetPriority( _irq_t irq, uint32_t priority )
{
    uint32_t *pIPRx = IPRx_START;
    uint8_t position;

    pIPRx = pIPRx + (irq/4);
    
    position = (irq % 4) * 8;
    
    *pIPRx &= ~(0xFF << position); //clar bits
    *pIPRx |= ((priority & 3) << (position + 6)); // write bits
}

uint32_t nvic_GetPriority( _irq_t irq )
{
    uint32_t *pIPRx = IPRx_START;
    uint8_t position;
    uint32_t priority;

    pIPRx = pIPRx + (irq/4);
    position = (irq % 4) * 8;
    priority = (*pIPRx >> (position + 6)) & 3;  

    return priority;
}

void nvic_EnableIrq( _irq_t irq )
{
    uint32_t *pISER = ISER_START;

    *pISER |= (1 << (irq % 32));
}

void nvic_DisableIrq( _irq_t irq )
{
    uint32_t *pICER = ICER_START;

    *pICER |= (1 << (irq % 32));
}

uint32_t nvic_GetPendingIrq( _irq_t irq )
{
    uint32_t *pISPR = ISPR_START;

    return *pISPR;
}

void nvic_SetPendingIrq( _irq_t irq )
{
    uint32_t *pISPR = ISPR_START;

    *pISPR |= (1 << (irq % 32));
}

void nvic_ClearPendingIrq( _irq_t irq )
{
    uint32_t *pICPR = ICPR_START;

    *pICPR |= (1 << (irq % 32));
}