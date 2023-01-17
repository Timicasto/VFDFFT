#ifndef VFDFFT_FIRMWARE_OPT3001_H
#define VFDFFT_FIRMWARE_OPT3001_H
#include "types.h"
#include "stm32f4xx.h"

static const u8 OPT3001_I2C_ADDR = 0x44;

static const u8 OPT3001_CONFIG_REG_ADDR = 0x01;
static const u8 OPT3001_RESULT_REG_ADDR = 0x00;
static const u8 OPT3001_SET_LOW = 0x02;
static const u8 OPT3001_SET_HIGH = 0x03;
static const u8 OPT3001_MANU_ID = 0x7E;
static const u8 OPT3001_DEV_ID = 0x7F;

u8 initOPT3001(I2C_HandleTypeDef* i2c);
float readOPT3001(I2C_HandleTypeDef* i2c);

#endif //VFDFFT_FIRMWARE_OPT3001_H
