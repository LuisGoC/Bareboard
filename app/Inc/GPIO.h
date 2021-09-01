#ifndef _GPIO_H_
    #define _GPIO_H_

    #include "registers.h"
    #include "types.h"

    #define GPIO_PIN_0   ((uint16_t)0x0001)
    #define GPIO_PIN_1   ((uint16_t)0x0002)
    #define GPIO_PIN_2   ((uint16_t)0x0004)
    #define GPIO_PIN_3   ((uint16_t)0x0008)
    #define GPIO_PIN_4   ((uint16_t)0x0010)
    #define GPIO_PIN_5   ((uint16_t)0x0020)
    #define GPIO_PIN_6   ((uint16_t)0x0040)
    #define GPIO_PIN_7   ((uint16_t)0x0080)
    #define GPIO_PIN_8   ((uint16_t)0x0100)
    #define GPIO_PIN_9   ((uint16_t)0x0200)
    #define GPIO_PIN_10  ((uint16_t)0x0400)
    #define GPIO_PIN_11  ((uint16_t)0x0800)
    #define GPIO_PIN_12  ((uint16_t)0x1000)
    #define GPIO_PIN_13  ((uint16_t)0x2000)
    #define GPIO_PIN_14  ((uint16_t)0x4000)
    #define GPIO_PIN_15  ((uint16_t)0x8000)
    #define GPIO_PIN_ALL ((uint16_t)0xFFFF) 

    #define GPIO_MODE_INPUT       ((uint32_t)0x00000000)
    #define GPIO_MODE_OUTPUT      ((uint32_t)0x00000001)
    #define GPIO_MODE_ALT         ((uint32_t)0x00000002)
    #define GPIO_MODE_ANALOG      ((uint32_t)0x00000003)
    #define GPIO_MODE_IT_FALLING  ((uint32_t)0x00000004)
    #define GPIO_MODE_IT_RISING   ((uint32_t)0x00000005)
    #define GPIO_MODE_IT_BOTH     ((uint32_t)0x00000006)

    #define GPIO_AF0      ((uint32_t)0x00000000)
    #define GPIO_AF1      ((uint32_t)0x00000001)
    #define GPIO_AF2      ((uint32_t)0x00000002)
    #define GPIO_AF3      ((uint32_t)0x00000003)
    #define GPIO_AF4      ((uint32_t)0x00000004)
    #define GPIO_AF5      ((uint32_t)0x00000005)
    #define GPIO_AF6      ((uint32_t)0x00000006)
    #define GPIO_AF7      ((uint32_t)0x00000007)

    #define GPIO_NOPULL    	  ((uint32_t)0x00000000)
    #define GPIO_PULLUP    	  ((uint32_t)0x00000001)
    #define GPIO_PULLDOWN     ((uint32_t)0x00000002)

    #define GPIO_ADDRESS_TO_CODE(x)  ( (x == GPIOA_START) ? 0 : \
                                    (x == GPIOB_START) ? 1 : \
                                    (x == GPIOC_START) ? 2 : \
                                    (x == GPIOD_START) ? 3 : 0 )


    typedef struct
    {
        uint32_t Pin;                      
        uint32_t Mode;  	
        uint32_t Pull;  	
        uint32_t Alternate; 
    }gpioConfig_t;

    void gpio_configPort( GPIOx *port, gpioConfig_t *config );
    void gpio_writePort( GPIOx *port, uint32_t value );
    uint32_t gpio_readPort( GPIOx *port );
    void gpio_setPins( GPIOx *port, uint32_t pins );
    void gpio_resetPins( GPIOx *port, uint32_t pins );
    void gpio_togglePins( GPIOx *port, uint32_t pins );
    void gpio_writePins( GPIOx *port, uint32_t pins, uint32_t value );
    uint32_t gpio_readPin( GPIOx *port, uint32_t pin );
    void gpio_isrHandler( uint32_t pin );
    void gpio_isrCallback( uint32_t pin );


#endif