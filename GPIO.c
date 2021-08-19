#include "GPIO.h"
#include "registers.h"
#include "types.h"
#include "RCC.h"

void gpio_configPort( GPIOx *port, gpioConfig_t *config )
{
    int8_t PinPosition = 0;

    while((config->Pin >> PinPosition) != 0) 
    {
        if(BIT_STATE(config->Pin, PinPosition) == 1)
        {
            if(config->Mode <= GPIO_MODE_ANALOG)
            {
                port->MODER &= ~(3 << (PinPosition << 1));
                port->MODER |= (config->Mode << (PinPosition << 1));

                port->PUPDR &= ~(3 << (PinPosition << 1));
                port->PUPDR |= (config->Pull << (PinPosition << 1));
            }
            else
            {
                if(config->Mode == GPIO_MODE_IT_FALLING)
                {
                    BIT_SET(EXTI_START->FTSR, PinPosition);
                    BIT_RESET(EXTI_START->RTSR, PinPosition);
                }
                if(config->Mode == GPIO_MODE_IT_RISING)
                {
                    BIT_SET(EXTI_START->RTSR, PinPosition);
                    BIT_RESET(EXTI_START->FTSR, PinPosition);
                }
                if(config->Mode == GPIO_MODE_IT_BOTH)
                {
                    BIT_SET(EXTI_START->FTSR, PinPosition);
                    BIT_SET(EXTI_START->RTSR, PinPosition);
                } 
                
                RCC_SYSCFG_CLOCK_ON();
                SYSCFG_START->EXTICR[PinPosition/4] = GPIO_ADDRESS_TO_CODE(port) << ((PinPosition % 4) << 2); 
                BIT_SET(EXTI_START->IMR, PinPosition);
            }
        }
        PinPosition++;
    }
}

void gpio_writePort( GPIOx *port, uint32_t value )
{
    port->BSRR = 0xFFFF0000u;
    port->BSRR = (value & 0xFFFFu);
}

uint32_t gpio_readPort( GPIOx *port )
{
    uint32_t value = 0;
    value |= port->IDR;
    return value;
}

void gpio_setPins( GPIOx *port, uint32_t pins )
{
    port->BSRR = (0xFFFFu & pins);
}

void gpio_resetPins( GPIOx *port, uint32_t pins )
{
    port->BSRR = (pins << 16);
}

void gpio_togglePins( GPIOx *port, uint32_t pins )
{
    port->ODR ^= (0xFFFFu & pins); // (no read/modify/write) avoid irq 
}

void gpio_writePins( GPIOx *port, uint32_t pins, uint32_t value )
{
    if(value != 0)
    {
        port->BSRR = (0xFFFFu & pins);
    }
    else
    {
        port->BSRR = (pins << 16);
    }
}

uint32_t gpio_readPin( GPIOx *port, uint32_t pin )
{
    uint32_t state;

    if((port->IDR & (pin & 0xFFFFu)) != 0)
    {
        state = 1;
    }
    else
    {
        state = 0;
    }

    return state;
}

void gpio_isrHandler( uint32_t pin )
{
    uint8_t PinPosition = 0;
    while((pin >> PinPosition) != 0) 
    {
        if(BIT_STATE(EXTI_START->PR, PinPosition))
        {
            BIT_SET(EXTI_START->PR, PinPosition);
            gpio_isrCallback(PinPosition);
        }
        PinPosition++;
    }
}

__attribute__((weak)) void gpio_isrCallback( uint32_t pin )
{
    
}