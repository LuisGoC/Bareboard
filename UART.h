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
    #define UART_PARITY_EVEN         ((uint32_t)0x00000001)
    #define UART_PARITY_ODD          ((uint32_t)0x00000002)

    #define UART_MODE_TX             ((uint32_t)0x00000000)
    #define UART_MODE_RX             ((uint32_t)0x00000001)
    #define UART_MODE_TX_RX          ((uint32_t)0x00000002)

    typedef struct
    {
        USARTx *uart;                      
        uint32_t BaudRate;  	
        uint32_t WordLength;  	
        uint32_t StopBits;
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