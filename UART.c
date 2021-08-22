#include "UART.h"
#include "registers.h"
#include "types.h"
#include "RCC.h"

void uart_configPort( uartConfig_t *uartH )
{
    uart_mspInit(uartH);

    // Program the M bit in USART_CR1 to define the word length. 
    //uartH->uart->CR1 &=  ~(1 << USART_CR1_M0);
    BIT_RESET(uartH->uart->CR1, USART_CR1_M0);
    uartH->uart->CR1 |= ((uartH->WordLength & 1u) << USART_CR1_M0);

    //program parity control
    uartH->uart->CR1 &= ~(3 << USART_CR1_PS);
    uartH->uart->CR1 |= ((uartH->Parity & 3) << USART_CR1_PS);

    // Program the oversampling
    BIT_RESET(uartH->uart->CR1, USART_CR1_OVER8);
    uartH->uart->CR1 |= ((uartH->OverSampling & 1u) << USART_CR1_OVER8);

    //Select the desired baud rate using the USART_BRR register.
    uint16_t usartDiv;
    usartDiv = ((uartH->OverSampling+1)*SYSTEM_CLOCK_FREQ)/uartH->BaudRate;
    if(uartH->OverSampling == UART_OVERSAMPLING_16)
    {
        uartH->uart->BRR = usartDiv;
    }
    if(uartH->OverSampling == UART_OVERSAMPLING_8)
    {
        uartH->uart->BRR = (((0x000Fu & usartDiv) >> 1) | (0xFFF0u & usartDiv));
    }

    //Program the number of stop bits in USART_CR2.
    uartH->uart->CR2 &= ~(3 << USART_CR2_STOP);
    uartH->uart->CR2 |= ((uartH->StopBits & 3) << USART_CR2_STOP);

    //Program TE and RE bits 
    // uartH->uart->CR1 &= ~(3 << USART_CR1_RE);
    // uartH->uart->CR1 |= ((uartH->TxRxMode & 3) << USART_CR1_RE);

    //Enable the USART by writing the UE bit in USART_CR1 register to 1.
    BIT_SET(uartH->uart->CR1, USART_CR1_UE);

}

__attribute__((weak)) void uart_mspInit( uartConfig_t *uartH )
{

}

void uart_sendBuffer( uartConfig_t *uartH, uint8_t *ptr, uint32_t len )
{
    uint16_t count = 0;

    uartH->uart->CR1 &= ~(1 << USART_CR1_TE);
    uartH->uart->CR1 |= (1 << USART_CR1_TE);
    
    while(count < len)
    {
        if(BIT_STATE(uartH->uart->ISR, USART_ISR_TXE))
        {
            uartH->uart->TDR = ptr[count];
            while(BIT_STATE(uartH->uart->ISR, USART_ISR_TC) != 1)
            {
                //wait for TC bit flag
            }
            count++;
        }
    }
}

void uart_sendBufferInt( uartConfig_t *uartH, uint8_t *ptr, uint32_t len )
{

}

void uart_receiveBufferInt( uartConfig_t *uartH, uint8_t *ptr, uint32_t len )
{

}

void uart_isrHandler( uartConfig_t *uartH )
{

}

__attribute__((weak)) void uart_isrTxCallback( uartConfig_t *uartH )
{

}

__attribute__((weak)) void uart_isrRxCallback( uartConfig_t *uart )
{

}