#ifndef _UART_H_
    #define _UART_H_

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

    #define USART_CR1_UE     0u
    #define USART_CR1_RE     2u
    #define USART_CR1_TE     3u
    #define USART_CR1_IDELIE 4u
    #define USART_CR1_RXNEIE 5u
    #define USART_CR1_TCIE   6u
    #define USART_CR1_TXEIE  7u
    #define USART_CR1_PEIE   8u
    #define USART_CR1_PS     9u
    #define USART_CR1_PCE    10u
    #define USART_CR1_WAKE   11u 
    #define USART_CR1_M0     12u
    #define USART_CR1_MME    13u
    #define USART_CR1_CMIE   14u
    #define USART_CR1_OVER8  15u
    #define USART_CR1_RTOIE  26u
    #define USART_CR1_M1     28u

    #define USART_CR2_STOP   12u

    #define USART_ISR_TXE    7u
    #define USART_ISR_TC     6u

    #define SYSTEM_CLOCK_FREQ     8000000u

    typedef struct
    {
        USARTx *uart;                      
        uint32_t BaudRate;  	
        uint32_t WordLength;  	
        uint32_t StopBits;
        uint32_t OverSampling;
        uint32_t Parity;
        uint32_t TxRxMode; 
    }uartConfig_t;

void uart_configPort( uartConfig_t *uartH );
void uart_mspInit( uartConfig_t *uartH );
void uart_sendBuffer( uartConfig_t *uartH, uint8_t *ptr, uint32_t len );
void uart_sendBufferInt( uartConfig_t *uartH, uint8_t *ptr, uint32_t len );
void uart_receiveBufferInt( uartConfig_t *uartH, uint8_t *ptr, uint32_t len );
void uart_isrHandler( uartConfig_t *uartH );
void uart_isrTxCallback( uartConfig_t *uartH );
void uart_isrRxCallback( uartConfig_t *uart );

#endif