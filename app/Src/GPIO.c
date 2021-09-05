#include "GPIO.h"
#include "registers.h"
#include "types.h"
#include "RCC.h"

void gpio_configPort( GPIOx *port, gpioConfig_t *config )
{
    uint32_t PinPosition = 0;

    while((config->Pin >> PinPosition) != 0UL) 
    {
        if(BIT_STATE(config->Pin, PinPosition) == 1UL)
        {
            if(config->Mode <= GPIO_MODE_ANALOG)
            {
                port->MODER &= ~(3UL << (PinPosition << 1UL));
                port->MODER |= (config->Mode << (PinPosition << 1UL));

                port->PUPDR &= ~(3UL << (PinPosition << 1UL));
                port->PUPDR |= (config->Pull << (PinPosition << 1UL));

                if(config->Mode == GPIO_MODE_ALT)
                {
                    port->AFR[PinPosition/8UL] &= ~(0xFUL << ((PinPosition % 8UL) << 2UL));
                    port->AFR[PinPosition/8UL] |= ((config->Alternate & 0xFUL) << ((PinPosition % 8UL) << 2UL));
                }
            }
            else
            {
                /*Interrupt mode*/
                if(config->Mode == GPIO_MODE_IT_FALLING)
                {
                    /* cppcheck supress of an advisory rule because we need to modify a pointer to variable register value */
                    BIT_SET(EXTI_START->FTSR, PinPosition); /* cppcheck-suppress misra-c2012-11.4*/
                    BIT_RESET(EXTI_START->RTSR, PinPosition); /* cppcheck-suppress misra-c2012-11.4*/
                }
                if(config->Mode == GPIO_MODE_IT_RISING)
                {
                    /* cppcheck supress of an advisory rule because we need to modify a pointer to variable register value */
                    BIT_SET(EXTI_START->RTSR, PinPosition); /* cppcheck-suppress misra-c2012-11.4*/
                    BIT_RESET(EXTI_START->FTSR, PinPosition); /* cppcheck-suppress misra-c2012-11.4*/
                }
                if(config->Mode == GPIO_MODE_IT_BOTH)
                {
                    /* cppcheck supress of an advisory rule because we need to modify a pointer to variable register value */
                    BIT_SET(EXTI_START->FTSR, PinPosition); /* cppcheck-suppress misra-c2012-11.4*/
                    BIT_SET(EXTI_START->RTSR, PinPosition); /* cppcheck-suppress misra-c2012-11.4*/
                } 
                
                RCC_SYSCFG_CLOCK_ON(); /* cppcheck-suppress misra-c2012-11.4*/
                SYSCFG_START->EXTICR[PinPosition/4UL] &=  ~(0xFFUL << ((PinPosition % 4UL) << 2UL)); /* cppcheck-suppress misra-c2012-11.4*/
                SYSCFG_START->EXTICR[PinPosition/4UL] |= GPIO_ADDRESS_TO_CODE(port) << ((PinPosition % 4UL) << 2UL); /* cppcheck-suppress misra-c2012-11.4*/
                BIT_SET(EXTI_START->IMR, PinPosition); /* cppcheck-suppress misra-c2012-11.4*/
                /* cppcheck supress of an advisory rule because we need to modify a pointer to variable register value */
            }
        }
        PinPosition++;
    }
}

void gpio_writePort( GPIOx *port, uint32_t value )
{
    port->BSRR = 0xFFFF0000u;
    port->BSRR = (value & 0xFFFFUL);
}

uint32_t gpio_readPort( GPIOx *port )
{
    uint32_t value = 0;
    value |= port->IDR;
    return value;
}

void gpio_setPins( GPIOx *port, uint32_t pins )
{
    port->BSRR = (0xFFFFUL & pins);
}

void gpio_resetPins( GPIOx *port, uint32_t pins )
{
    port->BSRR = (pins << 16UL);
}

void gpio_togglePins( GPIOx *port, uint32_t pins )
{
    port->ODR ^= (0xFFFFUL & pins); // (no read/modify/write) avoid irq 
}

void gpio_writePins( GPIOx *port, uint32_t pins, uint32_t value )
{
    if(value != 0UL)
    {
        port->BSRR = (0xFFFFUL & pins);
    }
    else
    {
        port->BSRR = (pins << 16UL);
    }
}

uint32_t gpio_readPin( GPIOx *port, uint32_t pin )
{
    uint32_t state;

    if((port->IDR & (pin & 0xFFFFUL)) != 0UL)
    {
        state = 1UL;
    }
    else
    {
        state = 0UL;
    }

    return state;
}

void gpio_isrHandler( uint32_t pin )
{
    if((EXTI_START->PR & pin) != 0UL) /* cppcheck-suppress misra-c2012-11.4*/
    {
        /* cppcheck supress of an advisory rule because we need to modify a pointer to variable register value */
        EXTI_START->PR |= pin; /* cppcheck-suppress misra-c2012-11.4*/
        gpio_isrCallback(pin);
    }
}

__attribute__((weak)) void gpio_isrCallback( uint32_t pin )
{
    (void)pin;
}