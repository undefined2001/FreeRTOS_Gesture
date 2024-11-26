#ifndef __INC_MPU6050_H__
#define __INC_MPU6050_H__

#include "i2c.h"

#define MPU_ADDRESS 0x68U

void MPU_Init();
uint8_t MPU_Whoami();

#endif