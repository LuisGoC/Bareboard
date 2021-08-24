
#include "GPIO.h"
#include "UART.h"
#include "RCC.h"
#include "NVIC.h"
#include <stdlib.h>
#define LED_PIN      5

//extern void initialise_monitor_handles(void);
static gpioConfig_t gpioHandle;
static uartConfig_t uartHandle;
uint8_t RxBuffer[10];
uint8_t RxByte;
uint8_t counter = 0;
volatile uint8_t stat = 0;

int main ( void )
{
    uint32_t delay = 10000;

    /* Enable clock for GPIO port A, RCC_AHBENR bit  */
    RCC_GPIOA_CLOCK_ON();

    /* Configure GPIOA pin 5 as output */
    gpioHandle.Mode = GPIO_MODE_OUTPUT;
    gpioHandle.Pin = GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7 | GPIO_PIN_8 | GPIO_PIN_10;
    gpioHandle.Pull = GPIO_NOPULL;
    gpio_configPort(GPIOA_START, &gpioHandle);
    
    uartHandle.uart = USART2_START;
    uartHandle.BaudRate = 9600;
    uartHandle.TxRxMode = UART_MODE_TX_RX;
    uartHandle.OverSampling = UART_OVERSAMPLING_16;
    uartHandle.Parity = UART_PARITY_NONE;
    uartHandle.StopBits = UART_STOPBITS_1;
    uartHandle.WordLength = UART_WORDLENGTH_8B;
    uart_configPort(&uartHandle);

    uart_receiveBufferInt(&uartHandle, &RxByte, 1);
    for(;;)
    {
        if(stat == 1)
        {
            stat = 0;
            //uart_sendBuffer(&uartHandle, RxBuffer, counter);
            delay = atoi((char *)RxBuffer);
            for(uint8_t i = 0; i < counter; i++)
            {
                RxBuffer[i] = 0;
            }
            counter = 0;
        }
        gpio_togglePins(GPIOA_START, GPIO_PIN_5);
        _delay(delay);
    }
}

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
    nvic_SetPriority(USART2_IRQn, 2);
    nvic_EnableIrq(USART2_IRQn);
}

void USART2_IRQHandler(void)
{
    uart_isrHandler( &uartHandle );
}

void uart_isrRxCallback( uartConfig_t *uart )
{
    static uint32_t i = 0; 
    RxBuffer[i] = RxByte;
    i++; 
    if(RxBuffer[i-1] == '\r')
    { 
        counter = i;
        stat = 1; 
        i = 0; 
    }
    uart_receiveBufferInt(&uartHandle, &RxByte, 1);
}

void uart_isrTxCallback( uartConfig_t *uart )
{
    // gpio_togglePins(GPIOA_START, GPIO_PIN_5);
}