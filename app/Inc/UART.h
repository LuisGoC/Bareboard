#ifndef UART_H_
    #define UART_H_

    #include "types.h" 
    #include "registers.h"

    #define UART_WORDLENGTH_8B       ((uint32_t)0x00000000)
    #define UART_WORDLENGTH_9B       ((uint32_t)0x00000001)

    #define UART_STOPBITS_0_5        ((uint32_t)0x00000001) //reserved
    #define UART_STOPBITS_1          ((uint32_t)0x00000000)
    #define UART_STOPBITS_1_5        ((uint32_t)0x00000003) //reserved
    #define UART_STOPBITS_2          ((uint32_t)0x00000002)

    #define UART_PARITY_NONE         ((uint32_t)0x00000000)
    #define UART_PARITY_EVEN         ((uint32_t)0x00000002)
    #define UART_PARITY_ODD          ((uint32_t)0x00000003)

    #define UART_OVERSAMPLING_16     ((uint32_t)0x00000000)
    #define UART_OVERSAMPLING_8      ((uint32_t)0x00000001)

    #define UART_MODE_TX             ((uint32_t)0x00000002)
    #define UART_MODE_RX             ((uint32_t)0x00000001)
    #define UART_MODE_TX_RX          ((uint32_t)0x00000003)

    #define USART_CR1_UE     0UL
    #define USART_CR1_RE     2UL
    #define USART_CR1_TE     3UL
    #define USART_CR1_IDELIE 4UL
    #define USART_CR1_RXNEIE 5UL
    #define USART_CR1_TCIE   6UL
    #define USART_CR1_TXEIE  7UL
    #define USART_CR1_PEIE   8UL
    #define USART_CR1_PS     9UL
    #define USART_CR1_PCE    10UL
    #define USART_CR1_WAKE   11UL
    #define USART_CR1_M0     12UL
    #define USART_CR1_MME    13UL
    #define USART_CR1_CMIE   14UL
    #define USART_CR1_OVER8  15UL
    #define USART_CR1_RTOIE  26UL
    #define USART_CR1_M1     28UL

    #define USART_CR2_STOP   12UL

    #define USART_ISR_TXE    7UL
    #define USART_ISR_TC     6UL
    #define USART_ISR_RXNE   5UL

    #define SYSTEM_CLOCK_FREQ     8000000UL

    typedef struct
    {
        USARTx *uart;                      
        uint32_t BaudRate;  	
        uint32_t WordLength;  	
        uint32_t StopBits;
        uint32_t OverSampling;
        uint32_t Parity;
        uint32_t TxRxMode; 
        uint8_t *pRxData;
        uint32_t RxLen;
        uint8_t *pTxData;
        uint32_t TxLen;
    }uartConfig_t;

void uart_configPort( uartConfig_t *uartH );
void uart_mspInit( uartConfig_t *uartH );
void uart_sendBuffer( uartConfig_t *uartH, uint8_t *ptr, uint32_t len );
void uart_sendBufferInt( uartConfig_t *uartH, uint8_t *ptr, uint32_t len );
void uart_receiveBufferInt( uartConfig_t *uartH, uint8_t *ptr, uint32_t len );
void uart_isrHandler( uartConfig_t *uartH );
void uart_isrTxCallback( uartConfig_t *uartH );
void uart_isrRxCallback( uartConfig_t *uartH );

#endif