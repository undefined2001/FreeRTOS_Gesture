#include "i2c.h"

/**
 * @brief: Few Private Helper functions(Start Sections)
 */

// Generates the Start Signal
static void I2C_Start(I2C_TypeDef *pI2Cx)
{
    pI2Cx->CR1 |= I2C_CR1_START;
}

// Enables the I2C Peripherals
static void I2C_Enable(I2C_TypeDef *pI2Cx)
{
    pI2Cx->CR1 |= I2C_CR1_PE;
}

// Disables the I2C Peripherals
static void I2C_Disable(I2C_TypeDef *pI2Cx)
{
    pI2Cx->CR1 &= ~I2C_CR1_PE;
}

// Sets the Acknowlegement
static void I2C_SetACK(I2C_TypeDef *pI2Cx)
{
    pI2Cx->CR1 |= I2C_CR1_ACK;
}

// Resets the Acknowlegement
static void I2C_ResetACK(I2C_TypeDef *pI2Cx)
{
    pI2Cx->CR1 &= ~I2C_CR1_ACK;
}
/**
 * @brief: Few Private Helper functions(End Section)
 */

/**
 * @brief: This Api is used to Configure the I2C Peripheral
 */
void I2C_Init(I2C_Config_t *pConfig)
{
}

/**
 * @brief: Funciton for Sending a Byte
 */

void I2C_MasterSendByte(I2C_Config_t *Config, uint8_t byte)
{
    //Sending Byte
}