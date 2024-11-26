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
    uint32_t CCRValue, FreqValue;

    uint32_t PCLK = 16000000;

    // Enabling Clock
    if (pConfig->pI2Cx == I2C1)
    {
        __RCC_I2C1_CLK_EN();
    }
    else if (pConfig->pI2Cx == I2C2)
    {
        __RCC_I2C2_CLK_EN();
    }
    else if (pConfig->pI2Cx == I2C3)
    {
        __RCC_I2C3_CLK_EN();
    }

    // Disable the peripheral for configuration
    I2C_Enable(pConfig->pI2Cx);

    FreqValue = PCLK / 1000000UL;

    // Reset the peripheral
    pConfig->pI2Cx->CR1 |= I2C_CR1_SWRST;
    pConfig->pI2Cx->CR1 &= ~I2C_CR1_SWRST;

    // Configure the peripheral
    pConfig->pI2Cx->CR2 |= (FreqValue & 0x3F);

    // Calculate and set the CCR value
    if (pConfig->SCLSpeed <= I2C_SM_SPEED_100KHz)
    {
        CCRValue = (PCLK / (2U * pConfig->SCLSpeed));
    }
    else
    {
        if (pConfig->DutyCycle == I2C_FM_DUTY_2)
        {
            CCRValue = (PCLK / (3U * pConfig->SCLSpeed));
        }
        else if (pConfig->DutyCycle == I2C_FM_DUTY_16_9)
        {
            CCRValue = (PCLK / (25U * pConfig->SCLSpeed));
        }
    }

    pConfig->pI2Cx->CCR = CCRValue & 0xFFF;

    // Configure the TRISE value
    pConfig->pI2Cx->TRISE = FreqValue + 1;

    // Enable the peripheral
    I2C_Enable(pConfig->pI2Cx);

    // Enabling Acking
    I2C_SetACK(pConfig->pI2Cx);
}
/**
 * @brief: Funciton for Sending a Byte
 */

void I2C_MasterSendByte(I2C_Config_t *pConfig, uint8_t byte)
{
    // Generating the Start Condition
    I2C_Start(pConfig->pI2Cx);

    // Sending the Address
    pConfig->pI2Cx->DR = pConfig->Address;

    // Clearing Addr Flag
    while (!(pConfig->pI2Cx->SR1 & I2C_SR1_ADDR))
        ;

    // Clearing Status Registers
    (void)pConfig->pI2Cx->SR1;
    (void)pConfig->pI2Cx->SR2;

    // Sending Byte
    pConfig->pI2Cx->DR = byte;

    //Waiting for the TX buffer to be empty
    while (!(pConfig->pI2Cx->SR1 & I2C_SR1_TXE))
}