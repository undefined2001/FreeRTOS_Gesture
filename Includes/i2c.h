#ifndef __INC_I2C_H__
#define __INC_I2C_H__

#include "stm32f446xx.h"

#define __RCC_I2C1_CLK_EN() (RCC->APB1ENR |= RCC_APB1ENR_I2C1EN)
#define __RCC_I2C2_CLK_EN() (RCC->APB1ENR |= RCC_APB1ENR_I2C2EN)
#define __RCC_I2C3_CLK_EN() (RCC->APB1ENR |= RCC_APB1ENR_I2C3EN)

#define I2C_SM_SPEED_100KHz 100000U
#define I2C_FM_SPEED_200KHz 200000U
#define I2C_FM_SPEED_250KHz 250000U
#define I2C_FM_SPEED_300KHz 300000U
#define I2C_FM_SPEED_350KHz 350000U
#define I2C_FM_SPEED_400KHz 400000U

#define I2C_FM_DUTY_2 0
#define I2C_FM_DUTY_16_9 1U
typedef struct
{
    I2C_TypeDef *pI2Cx;
    uint32_t SCLSpeed;
    uint32_t DutyCycle;
    uint32_t Address;
} I2C_Config_t;

void I2C_Init(I2C_Config_t *pConfig);
void I2C_MasterSendByte(I2C_Config_t *pConfig, uint8_t byte);

#endif