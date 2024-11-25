#ifndef __INC_UART_H__
#define __INC_UART_H__

#include "stm32f446xx.h"

// Define possible UART events
#define UART_EVENT_TX_COMPLETE 1
#define UART_EVENT_RX_COMPLETE 2
#define UART_EVENT_ERROR 3

// Word length for UART
typedef enum
{
    UART_WORD_LEN_8BITS = 0,
    UART_WORD_LEN_9BITS = 1
} UART_WordLen_t;

// UART mode selection
typedef enum
{
    UART_MODE_BOTH = 0,
    UART_MODE_TX_ONLY = 1,
    UART_MODE_RX_ONLY = 2
} UART_Mode_t;

// Parity options
typedef enum
{
    UART_PARITY_NONE = 0U,
    UART_PARITY_EVEN = 1U,
    UART_PARITY_ODD = 2U
} UART_Parity_t;

// Main configuration structure for UART
typedef struct
{
    uint32_t BaudRate;
    UART_Mode_t Mode;
    UART_Parity_t Parity;
    UART_WordLen_t WordLen;
} UART_Init_t;

// Data management structure for UART operations
typedef struct
{
    USART_TypeDef *pUARTx; // UART peripheral base address
    UART_Init_t Init;
    uint32_t State;
    uint32_t TxLen;
    uint32_t RxLen;
    uint8_t *pTxBuffer;
    uint8_t *pRxBuffer;
    uint32_t size;
} UARTConfig_t;

// Initialization function
void UART_Init(UARTConfig_t *config);
void UART2_GPIO_Init();

// Transmit and receive functions
void UART_SendChar(USART_TypeDef *pUARTx, uint8_t ch);
void UART_SendBuffer(USART_TypeDef *pUARTx, uint8_t *p_buffer, uint8_t len);
void UART_SendBufferIT(USART_TypeDef *pUARTx, uint8_t *p_buffer, uint8_t len);
void UART_SendBufferDMA(USART_TypeDef *pUARTx, uint8_t *p_buffer, uint8_t len);
void UART_RecvChar(USART_TypeDef *pUARTx, uint8_t *p_char);
void UART_RecvBuffer(USART_TypeDef *pUARTx, uint8_t *p_buffer, uint8_t len);
void UART_RecvBufferIT(USART_TypeDef *pUARTx, uint8_t *p_buffer, uint8_t len);
void UART_RecvBufferDMA(USART_TypeDef *pUARTx, uint8_t *p_buffer, uint8_t len);

// Event callback function (to be implemented by the user as needed)
__attribute__((weak)) void UART_ApplicationEventCallback(UARTConfig_t *pConfig, uint8_t EventType);

#endif // __INC_UART_H__