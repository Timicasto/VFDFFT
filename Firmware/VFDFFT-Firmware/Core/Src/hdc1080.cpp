#include "hdc1080.h"
#include "stm32f4xx.h"

void initHDC1080(I2C_HandleTypeDef* i2c) {
	u16 regValTemp = 0x1000;
	u8 dataBuf[2];

	if (TEMP_RES == 1) {
		regValTemp |= (1 << 10);
	}

	switch (HUM_RES) {
		case 1:
			regValTemp |= (1 << 8);
			break;
		case 2:
			regValTemp |= (1 << 9);
			break;
		default:
			break;
	}

	dataBuf[0] = (regValTemp >> 8);
	dataBuf[1] = (regValTemp & 0x00FF);
	HAL_I2C_Mem_Write(i2c, HDC1080_I2C_ADDR << 1, HDC1080_CONFIG_REG_ADDR, I2C_MEMADD_SIZE_8BIT, dataBuf, 2, 1000);
}

TmpSensorData getHDC1080Data(I2C_HandleTypeDef* i2c) {
	u8 receivedData[4];
	u16 tempX, humX;
	u8 sendBuf = HDC1080_TEMP_REG_ADDR;

	HAL_I2C_Master_Transmit(i2c, HDC1080_I2C_ADDR << 1, &sendBuf, 1, 1000);
	// Delay Here: 15ms for conversion complete, datasheet say maximum is 7ms but when delay=7ms the data is incorrect.
	HAL_Delay(15);

	HAL_I2C_Master_Receive(i2c, HDC1080_I2C_ADDR << 1, receivedData, 4, 1000);
	tempX = ((receivedData[0] << 8) | receivedData[1]);
	humX = ((receivedData[2] << 8) | receivedData[3]);

	TmpSensorData data = {((tempX / 65536.0F) * 165.0F) - 40.0F, static_cast<u8>((u8)(humX / 65536.0) * 100.0)};

	return data;
}
