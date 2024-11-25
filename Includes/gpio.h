#ifndef __INC_GPIO_H__
#define __INC_GPIO_H__

#include "stm32f446xx.h"

/* Necessary Macros */
/** Macros for enabling GPIO Ports */
#define __RCC_GPIOA_CLK_EN() ((RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN))
#define __RCC_GPIOB_CLK_EN() ((RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN))
#define __RCC_GPIOC_CLK_EN() ((RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN))
#define __RCC_GPIOD_CLK_EN() ((RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN))
#define __RCC_GPIOE_CLK_EN() ((RCC->AHB1ENR |= RCC_AHB1ENR_GPIOEEN))
#define __RCC_GPIOF_CLK_EN() ((RCC->AHB1ENR |= RCC_AHB1ENR_GPIOFEN))
#define __RCC_GPIOG_CLK_EN() ((RCC->AHB1ENR |= RCC_AHB1ENR_GPIOGEN))
#define __RCC_GPIOH_CLK_EN() ((RCC->AHB1ENR |= RCC_AHB1ENR_GPIOHEN))

/** Macros for disabling GPIO Ports */
#define __RCC_GPIOA_CLK_DI() ((RCC->AHB1ENR &= ~RCC_AHB1ENR_GPIOAEN))
#define __RCC_GPIOB_CLK_DI() ((RCC->AHB1ENR &= ~RCC_AHB1ENR_GPIOBEN))
#define __RCC_GPIOC_CLK_DI() ((RCC->AHB1ENR &= ~RCC_AHB1ENR_GPIOCEN))
#define __RCC_GPIOD_CLK_DI() ((RCC->AHB1ENR &= ~RCC_AHB1ENR_GPIODEN))
#define __RCC_GPIOE_CLK_DI() ((RCC->AHB1ENR &= ~RCC_AHB1ENR_GPIOEEN))
#define __RCC_GPIOF_CLK_DI() ((RCC->AHB1ENR &= ~RCC_AHB1ENR_GPIOFEN))
#define __RCC_GPIOG_CLK_DI() ((RCC->AHB1ENR &= ~RCC_AHB1ENR_GPIOGEN))
#define __RCC_GPIOH_CLK_DI() ((RCC->AHB1ENR &= ~RCC_AHB1ENR_GPIOHEN))
/* Necessary Macros */

typedef enum
{
    GPIO_MODE_INPUT = 0U,
    GPIO_MODE_OUTPUT = 1U,
    GPIO_MODE_ALTFN = 2U,
    GPIO_MODE_ANALOG = 3U
} GPIO_Mode;

typedef enum
{
    GPIO_PUPD_NONE = 0U,
    GPIO_PUPD_PULLUP = 1U,
    GPIO_PUPD_PULLDOWN = 2U
} GPIO_Pupd;

typedef enum
{
    GPIO_OSPEED_LOW = 0U,
    GPIO_OSPEED_MEDIUM = 1U,
    GPIO_OSPEED_FAST = 2U,
    GPIO_OSPEED_HIGH = 3U
} GPIO_OSpeed;

typedef enum
{
    GPIO_OTYPE_PP = 0U,
    GPIO_OTYPE_OD = 1U,
} GPIO_OType;

typedef enum
{
    GPIO_PIN_LOW = 0U,
    GPIO_PIN_HIGH = 1U
} GPIO_PinState;

typedef struct
{
    uint32_t Pin;
    GPIO_Mode Mode;
    GPIO_OSpeed OSpeed;
    GPIO_OType OType;
    GPIO_Pupd PUPD;
    uint32_t AFn;
} GPIOConfig_t;

void GPIO_ClockEnable(GPIO_TypeDef *pGPIOx);
void GPIO_ClockDisable(GPIO_TypeDef *pGPIOx);
void GPIO_Init(GPIO_TypeDef *pGPIOx, GPIOConfig_t *pConfig);
void GPIO_WritePin(GPIO_TypeDef *pGPIOx, uint32_t Pin, GPIO_PinState PinState);

/**
 * @brief This Function takes an 16 bit value for 16 Pin
 * @param: pGPIOx:This is a Parameter which is a Pointer to GPIO_TypeDef
 * @param: Hex: This takes a 16-bit value for each pin a bit
 */
void GPIO_WritePort(GPIO_TypeDef *pGPIOx, uint32_t Hex);
uint32_t GPIO_ReadPin(GPIO_TypeDef *pGPIOx, uint32_t Pin);
uint32_t GPIO_ReadPort(GPIO_TypeDef *pGPIOx);

void GPIO_TogglePin(GPIO_TypeDef *pGPIOx, uint32_t Pin, uint32_t DToggle);

#endif