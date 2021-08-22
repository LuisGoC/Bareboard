
#include "GPIO.h"
#include "UART.h"
#include "RCC.h"
#include "NVIC.h"
#define LED_PIN      5

//extern void initialise_monitor_handles(void);
static gpioConfig_t gpioHandle;
static uartConfig_t uartHandle;
//volatile uint8_t buttonFlag = 0;

int main ( void )
{
    //initialise_monitor_handles();
    //printf("\n");
    /* Enable clock for GPIO port A, RCC_AHBENR bit  */
    RCC_GPIOA_CLOCK_ON();

    /* Configure GPIOA pin 5 as output */
    gpioHandle.Mode = GPIO_MODE_OUTPUT;
    gpioHandle.Pin = GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7 | GPIO_PIN_8 | GPIO_PIN_10;
    gpioHandle.Pull = GPIO_NOPULL;
    gpio_configPort(GPIOA_START, &gpioHandle);
    
    uartHandle.uart = USART2_START;
    uartHandle.BaudRate = 9600;
    uartHandle.OverSampling = UART_OVERSAMPLING_16;
    uartHandle.Parity = UART_PARITY_NONE;
    uartHandle.StopBits = UART_STOPBITS_1;
    uartHandle.WordLength = UART_WORDLENGTH_8B;
    uart_configPort(&uartHandle);

    // gpioHandle.Mode = GPIO_MODE_IT_BOTH;
    // gpioHandle.Pin = GPIO_PIN_13;
    // gpioHandle.Pull = GPIO_NOPULL;
    // gpio_configPort(GPIOC_START, &gpioHandle);

    // nvic_SetPriority(EXTI4_15_IRQn, 2);
    // nvic_EnableIrq(EXTI4_15_IRQn);
    //printf("%d\n", nvic_GetPendingIrq(RTC_IRQn));
    uint8_t a[5] = {'H', 'O', 'L', 'A'};

    for(;;)
    {
        // if(buttonFlag == 1)
        // {
        //     buttonFlag = 0;
        //     gpio_togglePins(GPIOA_START, GPIO_PIN_5);
        // }
        gpio_togglePins(GPIOA_START, GPIO_PIN_5);
        uart_sendBuffer(&uartHandle, a, 4);
        _delay(1000000);
    }
}

// void EXTI4_15_IRQHandler(void)
// {
//     gpio_isrHandler(GPIO_PIN_13);
// }

// void gpio_isrCallback( uint32_t pin )
// {
//     if(pin == GPIO_PIN_13)
//     {
//         buttonFlag = 1;
//     }
// }

void uart_mspInit( uartConfig_t *uartH )
{
    gpioConfig_t gpioHandle2;
    RCC_GPIOA_CLOCK_ON();
    RCC_USART2_CLOCK_ON();
    gpioHandle2.Pin = GPIO_PIN_2 | GPIO_PIN_3;
    gpioHandle2.Mode = GPIO_MODE_ALT;
    gpioHandle2.Pull = GPIO_NOPULL;
    gpioHandle2.Alternate = GPIO_AF1;
    gpio_configPort(GPIOA_START, &gpioHandle2);
    // HAL_NVIC_SetPriority(USART2_IRQn, 1, 0);
    // HAL_NVIC_EnableIRQ(USART2_IRQn);
}