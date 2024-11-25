#include "uart.h"
#include "gpio.h"

extern uint32_t SystemCoreClock;

static inline void UART_ClockEnable(USART_TypeDef *pUARTx)
{
    if (pUARTx == USART1)
    {
        RCC->APB2ENR |= RCC_APB2ENR_USART1EN;
    }
    else if (pUARTx == USART2)
    {
        RCC->APB1ENR |= RCC_APB1ENR_USART2EN;
    }
    else if (pUARTx == USART6)
    {
        RCC->APB2ENR |= RCC_APB2ENR_USART6EN;
    }
}

static inline void UART_Enable(USART_TypeDef *pUARTx)
{
    pUARTx->CR1 |= USART_CR1_UE;
}

static inline void UART_Disable(USART_TypeDef *pUARTx)
{
    pUARTx->CR1 &= ~USART_CR1_UE;
}

static inline void UART_ModeConfig(USART_TypeDef *pUARTx, UART_Mode_t mode)
{
    if (mode == UART_MODE_BOTH)
    {
        pUARTx->CR1 |= USART_CR1_TE | USART_CR1_RE;
    }
    else if (mode == UART_MODE_TX_ONLY)
    {
        pUARTx->CR1 |= USART_CR1_TE;
        pUARTx->CR1 &= ~USART_CR1_RE;
    }
    else if (mode == UART_MODE_RX_ONLY)
    {
        pUARTx->CR1 &= ~USART_CR1_TE;
        pUARTx->CR1 |= USART_CR1_RE;
    }
}

static inline void UART_BaudRateConfig(USART_TypeDef *pUARTx, uint32_t br)
{
    uint32_t usart_div = SystemCoreClock / br;
    pUARTx->BRR |= ((usart_div / 16U) << USART_BRR_DIV_Mantissa_Pos) | ((usart_div / 16U) << USART_BRR_DIV_Fraction_Pos);
}

static inline void UART_ParityConfig(USART_TypeDef *pUARTx, UART_Parity_t parity)
{
    if (parity == UART_PARITY_NONE)
    {
        pUARTx->CR1 &= ~USART_CR1_PCE;
    }
    else if (parity == UART_PARITY_EVEN)
    {
        pUARTx->CR1 |= USART_CR1_PCE;
        pUARTx->CR1 &= ~USART_CR1_PS;
    }
    else if (parity == UART_PARITY_ODD)
    {
        pUARTx->CR1 |= USART_CR1_PCE | USART_CR1_PS;
    }
}

static inline void UART_WordLenConfig(USART_TypeDef *pUARTx, UART_WordLen_t w_len)
{
    if (w_len == UART_WORD_LEN_8BITS)
    {
        pUARTx->CR1 &= ~USART_CR1_M;
    }
    if (w_len == UART_WORD_LEN_9BITS)
    {
        pUARTx->CR1 |= USART_CR1_M;
    }
}

static inline void UART_ReadyToSend(USART_TypeDef *pUARTx)
{
    while (!(pUARTx->SR & USART_SR_TXE))
        ;
}

void UART2_GPIO_Init()
{
    GPIOConfig_t Tx, Rx;
    Tx.Pin = 2;
    Tx.Mode = GPIO_MODE_ALTFN;
    Tx.OSpeed = GPIO_OSPEED_HIGH;
    Tx.OType = GPIO_OTYPE_OD;
    Tx.PUPD = GPIO_PUPD_PULLUP;
    Tx.AFn = 7U;

    Rx.Pin = 3;
    Rx.Mode = GPIO_MODE_ALTFN;
    Rx.OSpeed = GPIO_OSPEED_HIGH;
    Rx.OType = GPIO_OTYPE_OD;
    Rx.PUPD = GPIO_PUPD_PULLUP;
    Rx.AFn = 7U;

    GPIO_ClockEnable(GPIOA);
    GPIO_Init(GPIOA, &Tx);
    GPIO_Init(GPIOA, &Rx);
}

void UART_Init(UARTConfig_t *Config)
{
    UART_ClockEnable(Config->pUARTx); // Enable The clock for USART so that it can be modified

    UART_Disable(Config->pUARTx); // Disable the USART peripheral so that it can be Configured

    UART_ModeConfig(Config->pUARTx, Config->Init.Mode); // Setting Uart mode, ex: TX_ONLY, RX_ONLY, BOTH

    UART_BaudRateConfig(Config->pUARTx, Config->Init.BaudRate); // Setting Baud Rate for

    UART_ParityConfig(Config->pUARTx, Config->Init.Parity); // Setting the parity for better error handle

    UART_WordLenConfig(Config->pUARTx, Config->Init.WordLen); // Setting Word Length

    UART_Enable(Config->pUARTx); // Enabling Uart Peripheral
}

void UART_SendChar(USART_TypeDef *pUARTx, uint8_t ch)
{
    UART_ReadyToSend(pUARTx);
    pUARTx->DR = ch;
}

void UART_SendBuffer(USART_TypeDef *pUARTx, uint8_t *p_buffer, uint8_t len)
{
    while (*p_buffer && len)
    {
        UART_SendChar(pUARTx, (uint8_t)(*p_buffer));
        p_buffer++;
        len--;
    }
}

__attribute__((weak)) void UART_ApplicationEventCallback(UARTConfig_t *pConfig, uint8_t EventType) {}