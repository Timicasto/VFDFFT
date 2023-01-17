#ifndef VFDFFT_FIRMWARE_HDC1080_H
#define VFDFFT_FIRMWARE_HDC1080_H

#include "types.h"
#include "stm32f4xx.h"

static const u8 HDC1080_I2C_ADDR = 0x40;
static const u8 HDC1080_CONFIG_REG_ADDR = 0x02;
static const u8 HDC1080_TEMP_REG_ADDR = 0x00;
static const u8 HDC1080_HUMIDITY_REG_ADDR = 0x01;

static const u8 TEMP_RES = 0;
static const u8 HUM_RES = 0;

typedef struct TmpSensorData {
	float temp;
	u8 humidity;
} TmpSensorData;

void initHDC1080(I2C_HandleTypeDef* i2c);
TmpSensorData getHDC1080Data(I2C_HandleTypeDef* i2c);

#endif //VFDFFT_FIRMWARE_HDC1080_H
