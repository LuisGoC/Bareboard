#include "GPIO.h"
#include "registers.h"
#include "types.h"

void gpio_configPort( GPIOx *port, gpioConfig_t *config )
{
    int8_t PinPosition = 0;

    while(PinPosition <= 15)
    {
        if(BIT_STATE(config->Pin, PinPosition) == 1)
        {
            // port->MODER |= (config->Mode << (PinPosition << 1));
            // port->PUPDR |= (config->Pull << (PinPosition << 1));
            port->MODER &= ~(3 << (PinPosition << 1));
            port->MODER |= (config->Mode << (PinPosition << 1));
            port->PUPDR &= ~(3 << (PinPosition << 1));
            port->PUPDR |= (config->Pull << (PinPosition << 1));
        }
        
        PinPosition++;
    }
}

void gpio_writePort( GPIOx *port, uint32_t value )
{
    port->BSRR |= 0xFFFF0000u;
    port->ODR ^= (value & 0xFFFFu);
}

uint32_t gpio_readPort( GPIOx *port )
{
    int value = 0;
    value |= port->IDR;
    return value;
}

void gpio_setPins( GPIOx *port, uint32_t pins )
{
    port->BSRR |= (0xFFFFu & pins);
}

void gpio_resetPins( GPIOx *port, uint32_t pins )
{
    port->BSRR |= (pins << 16);
}

void gpio_togglePins( GPIOx *port, uint32_t pins )
{
    port->ODR ^= (0xFFFFu & pins);
}

void gpio_writePins( GPIOx *port, uint32_t pins, uint32_t value )
{
    if(value != 0)
    {
        port->BSRR |= (0xFFFFu & pins);
    }
    else
    {
        port->BSRR |= (pins << 16);
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