#include <math.h>
#include "opt3001.h"

static const u16 CONFIG_DATA = 0xCE10; // Works in continuous mode by default

void writeToOPT3001(I2C_HandleTypeDef* i2c, u8 regAddr, u16 data) {
	u8 buffer[3];
	buffer[0] = regAddr;
	buffer[1] = (data) >> 8;
	buffer[2] = (data) & 0x00FF;

	HAL_I2C_Master_Transmit(i2c, OPT3001_I2C_ADDR << 1, buffer, 3, 50);
}

u16 readFromOPT3001(I2C_HandleTypeDef* i2c) {
	u8 readBuf[2];
	u16 receivedData;

	HAL_I2C_Master_Receive(i2c, OPT3001_I2C_ADDR << 1, readBuf, 2, 50);
	receivedData = ((readBuf[0] << 8) | readBuf[1]);

	return receivedData;
}

u8 initOPT3001(I2C_HandleTypeDef* i2c) {
	if (HAL_I2C_IsDeviceReady(i2c, OPT3001_I2C_ADDR << 1, 1, 20000) != HAL_OK) {
		return 0;
	}

	writeToOPT3001(i2c, OPT3001_CONFIG_REG_ADDR, CONFIG_DATA);
	return 1;
}

float readOPT3001(I2C_HandleTypeDef* i2c) {
	u16 iExponent, iMantissa;
	float ret;
	u16 raw;

	writeToOPT3001(i2c, OPT3001_RESULT_REG_ADDR,  0x00);
	HAL_Delay(50);
	raw = readFromOPT3001(i2c);
	iMantissa = raw & 0x0FFF;
	iExponent = (raw & 0xF000) >> 12;
	ret = iMantissa * (0.01 * powf(2, iExponent));

	return ret;
}