#include "mpu6050.h"

uint8_t MPU_Whoami()
{
    uint8_t data = 0x75; // WHOAMI Register Address
    uint8_t check;
    I2C1_GenStart();
    I2C1_SendAddress(MPU_ADDRESS, 0);
    I2C1_MasterSendData(&data, sizeof(data));
    // I2C1_GenStop();
    I2C1_GenStart();
    I2C1_SendAddress(MPU_ADDRESS, 1);
    I2C1_MasterReceiveData(&check, sizeof(check));
    return check;
}