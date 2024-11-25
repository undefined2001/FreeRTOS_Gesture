#ifndef __INC_I2C_H__
#define __INC_I2C_H__

#include "stm32f446xx.h"

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