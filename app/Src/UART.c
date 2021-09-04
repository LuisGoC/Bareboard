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
    uartH->uart->CR1 &= ~(3UL << USART_CR1_PS);
    uartH->uart->CR1 |= ((uartH->Parity & 3UL) << USART_CR1_PS);

    // Program the oversampling
    BIT_RESET(uartH->uart->CR1, USART_CR1_OVER8);
    uartH->uart->CR1 |= ((uartH->OverSampling & 1UL) << USART_CR1_OVER8);

    //Select the desired baud rate using the USART_BRR register.
    uint32_t usartDiv;
    usartDiv = ((uartH->OverSampling+1UL)*SYSTEM_CLOCK_FREQ)/uartH->BaudRate;
    if(uartH->OverSampling == UART_OVERSAMPLING_16)
    {
        uartH->uart->BRR = usartDiv;
    }
    if(uartH->OverSampling == UART_OVERSAMPLING_8)
    {
        uartH->uart->BRR = (((0x000FUL & usartDiv) >> 1UL) | (0xFFF0UL & usartDiv));
    }

    //Program the number of stop bits in USART_CR2.
    uartH->uart->CR2 &= ~(3UL << USART_CR2_STOP);
    uartH->uart->CR2 |= ((uartH->StopBits & 3UL) << USART_CR2_STOP);

    //Program TE and RE bits 
    uartH->uart->CR1 &= ~(3UL << USART_CR1_RE);
    uartH->uart->CR1 |= ((uartH->TxRxMode & 3UL) << USART_CR1_RE);

    //Enable the USART by writing the UE bit in USART_CR1 register to 1.
    BIT_SET(uartH->uart->CR1, USART_CR1_UE);

}

__attribute__((weak)) void uart_mspInit( uartConfig_t *uartH )
{
    (void)uartH;
}

void uart_sendBuffer( uartConfig_t *uartH, uint8_t *ptr, uint32_t len )
{
    uint16_t count = 0;
    
    while(count < len)
    {
        if(BIT_STATE(uartH->uart->ISR, USART_ISR_TXE) == 1UL)
        {
            uartH->uart->TDR = ptr[count];
            count++;
        }
    }
}

void uart_sendBufferInt( uartConfig_t *uartH, uint8_t *ptr, uint32_t len )
{
    if((ptr != ((void *)0)) && (len != 0UL))
    {
        uartH->pTxData = ptr;
        uartH->TxLen = len;
        BIT_SET(uartH->uart->CR1, USART_CR1_TXEIE);
    }
}

void uart_receiveBufferInt( uartConfig_t *uartH, uint8_t *ptr, uint32_t len )
{
    if((ptr != ((void *)0)) && (len != 0UL))
    {
        uartH->pRxData = ptr;
        uartH->RxLen = len;
        BIT_SET(uartH->uart->CR1, USART_CR1_RXNEIE);
    }
}

void uart_isrHandler( uartConfig_t *uartH )
{
    if(BIT_STATE(uartH->uart->ISR, USART_ISR_RXNE) == 1UL)
    {
        if(uartH->RxLen > 0UL)
        {
            *uartH->pRxData = uartH->uart->RDR;
            uartH->RxLen--;
            uartH->pRxData++;
        }
        else
        {
            BIT_RESET(uartH->uart->CR1, USART_CR1_RXNEIE);
            uart_isrRxCallback( uartH );
        }
    }
    if(BIT_STATE(uartH->uart->ISR, USART_ISR_TXE) == 1UL)
    {
        if(uartH->TxLen > 0UL)
        {
            uartH->uart->TDR = *uartH->pTxData;
            uartH->TxLen--;
            uartH->pTxData++;
        }
        else
        {
            BIT_RESET(uartH->uart->CR1, USART_CR1_TXEIE);
            uart_isrTxCallback( uartH );
        }
        
    }
}

__attribute__((weak)) void uart_isrTxCallback( uartConfig_t *uartH )
{
    (void)uartH;
}

__attribute__((weak)) void uart_isrRxCallback( uartConfig_t *uartH )
{
    (void)uartH;
}