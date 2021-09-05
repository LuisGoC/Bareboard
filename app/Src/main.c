
#include "GPIO.h"
#include "UART.h"
#include "RCC.h"
#include "NVIC.h"
#include <stdlib.h>

int32_t myAtoi(char* str);

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
    /* cppcheck supress of an advisory rule because we need to modify a pointer to variable register value */
    RCC_GPIOA_CLOCK_ON(); /* cppcheck-suppress misra-c2012-11.4*/

    /* Configure GPIOA pin 5 as output */
    gpioHandle.Mode = (uint32_t)GPIO_MODE_OUTPUT;
    gpioHandle.Pin = GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7 | GPIO_PIN_8 | GPIO_PIN_10;
    gpioHandle.Pull = (uint32_t)GPIO_NOPULL;
    gpio_configPort(GPIOA_START, &gpioHandle); /* cppcheck-suppress misra-c2012-11.4*/
     /* cppcheck supress of an advisory rule because we need to modify a pointer to variable register value */
    uartHandle.uart = USART2_START; /* cppcheck-suppress misra-c2012-11.4*/
    uartHandle.BaudRate = (uint32_t)9600;
    uartHandle.TxRxMode = (uint32_t)UART_MODE_TX_RX;
    uartHandle.OverSampling = (uint32_t)UART_OVERSAMPLING_16;
    uartHandle.Parity = (uint32_t)UART_PARITY_NONE;
    uartHandle.StopBits = (uint32_t)UART_STOPBITS_1;
    uartHandle.WordLength = (uint32_t)UART_WORDLENGTH_8B;
    uart_configPort(&uartHandle);

    uart_receiveBufferInt(&uartHandle, &RxByte, 1);
    for(;;)
    {
        if(stat == 1u)
        {
            stat = 0;
            //uart_sendBuffer(&uartHandle, RxBuffer, counter);
            delay = myAtoi((char *)RxBuffer);
            for(uint8_t i = 0; i < counter; i++)
            {
                RxBuffer[i] = 0;
            }
            counter = 0;
        }
        /* cppcheck supress of an advisory rule because we need to modify a pointer to variable register value */
        gpio_togglePins(GPIOA_START, GPIO_PIN_5); /* cppcheck-suppress misra-c2012-11.4*/
        _delay(delay);
    }
}

void uart_mspInit( uartConfig_t *uartH )
{
    /* cppcheck supress of an advisory rule because we need to modify a pointer to variable register value */
    (void)uartH;
    gpioConfig_t gpioHandle2;
    RCC_GPIOA_CLOCK_ON();  /* cppcheck-suppress misra-c2012-11.4*/
    RCC_USART2_CLOCK_ON(); /* cppcheck-suppress misra-c2012-11.4*/
    gpioHandle2.Pin = GPIO_PIN_2 | GPIO_PIN_3;
    gpioHandle2.Mode = (uint32_t)GPIO_MODE_ALT;
    gpioHandle2.Pull = (uint32_t)GPIO_NOPULL;
    gpioHandle2.Alternate = (uint32_t)GPIO_AF1;
    gpio_configPort(GPIOA_START, &gpioHandle2); /* cppcheck-suppress misra-c2012-11.4*/
    nvic_SetPriority(USART2_IRQn, 2);
    nvic_EnableIrq(USART2_IRQn);
}

void USART2_IRQHandler(void)
{
    uart_isrHandler( &uartHandle );
}

void uart_isrRxCallback( uartConfig_t *uartH )
{
    (void)uartH;
    static uint32_t i = 0; 
    RxBuffer[i] = RxByte;
    i++; 
    if(RxBuffer[i-1UL] == (uint8_t)'\r')
    { 
        counter = i;
        stat = 1; 
        i = 0; 
    }
    uart_receiveBufferInt(&uartHandle, &RxByte, 1);
}

void uart_isrTxCallback( uartConfig_t *uartH )
{
    (void)uartH;
}

int32_t myAtoi(char* str)
{
    int32_t res = 0;
    int32_t sign = 1;
    int32_t i = 0;
 
    // If number is negative,
    if (str[0] == '-') {
        sign = -1;
        // Also update index of first digit
        i++;
    }
 
    // Iterate through all digits
    // and update the result
    for (; str[i] != '\0'; ++i)
    {
        res = ((uint32_t)res * 10UL) + ((uint8_t)str[i] - (uint8_t)'0');
    }
    // Return result with sign
    return sign * res;
}