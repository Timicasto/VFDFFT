#include "pin_assignment.h"
#include "gp1287bi.h"

void sendCommandToGP1287BI(SPI_HandleTypeDef *spi, u8 total, ...) {
	va_list command;
	va_start(command, total);
	if (HAL_SPI_GetState(spi) == HAL_SPI_STATE_READY) {
		HAL_GPIO_WritePin(GP1287_CS_PORT, GP1287_CS_PIN, GPIO_PIN_RESET);
		for (int i = 0; i < total; ++i) {
			u8 data = va_arg(command, int);
			HAL_SPI_Transmit_DMA(spi, &data, 1);
		}
		while (HAL_SPI_GetState(spi) == HAL_SPI_STATE_BUSY_TX) {
			__NOP();
		}
		HAL_GPIO_WritePin(GP1287_CS_PORT, GP1287_CS_PIN, GPIO_PIN_SET);
	}
	va_end(command);
}

void writeDisplayDataToGP1287BI(SPI_HandleTypeDef *spi, u8 x, u8 y, u8 yLength, u8* data, u16 size) {
	if (HAL_SPI_GetState(spi) == HAL_SPI_STATE_READY) {
		HAL_GPIO_WritePin(GP1287_CS_PORT, GP1287_CS_PIN, GPIO_PIN_RESET);
		u8 sendBuf = 0xF0;
		HAL_SPI_Transmit_DMA(spi, &sendBuf, 1);
		HAL_SPI_Transmit_DMA(spi, &sendBuf, 1);
		y += 0x04;
		HAL_SPI_Transmit_DMA(spi, &sendBuf, 1);
		HAL_SPI_Transmit_DMA(spi, &sendBuf, 1);

		for (int i = 0; i < size; ++i) {
			HAL_SPI_Transmit_DMA(spi, &sendBuf, 1);
		}

		while (HAL_SPI_GetState(spi) == HAL_SPI_STATE_BUSY_TX) {
			__NOP();
		}
		HAL_GPIO_WritePin(GP1287_CS_PORT, GP1287_CS_PIN, GPIO_PIN_SET);
	}
}

void initGP1287BI(SPI_HandleTypeDef *spi) {
	HAL_GPIO_WritePin(GP1287_RST_PORT, GP1287_RST_PIN, GPIO_PIN_RESET);
	HAL_Delay(1);
	HAL_GPIO_WritePin(GP1287_RST_PORT, GP1287_RST_PIN, GPIO_PIN_SET);
	HAL_Delay(1);

	sendCommandToGP1287BI(spi, 1, 0xAA);
	sendCommandToGP1287BI(spi, 3, 0xCC, 0x02, 0x00);
	sendCommandToGP1287BI(spi, 8, 0xE0, 0xFF, 0x31, 0x00, 0x20, 0x00, 0x00, 0x00);
	sendCommandToGP1287BI(spi, 5, 0xB1, 0x20, 0x3F, 0x00, 0x01);
	sendCommandToGP1287BI(spi, 3, 0xA0, 0x00, 0x30);
	sendCommandToGP1287BI(spi, 1, 0x55);

	HAL_Delay(10);

	sendCommandToGP1287BI(spi, 3, 0xC0, 0x00, 0x04);
	sendCommandToGP1287BI(spi, 3, 0xD0, 0x00, 0x3C);
	sendCommandToGP1287BI(spi, 2, 0x90, 0x00);
	sendCommandToGP1287BI(spi, 2, 0x80, 0x00);
	sendCommandToGP1287BI(spi, 2, 0x08, 0x00);
}

void clearGP1287BI(SPI_HandleTypeDef *spi, u8 color) {
	if (HAL_SPI_GetState(spi) == HAL_SPI_STATE_READY) {
		HAL_GPIO_WritePin(GP1287_CS_PORT, GP1287_CS_PIN, GPIO_PIN_RESET);
		u8 sendBuf = 0xF0;
		HAL_SPI_Transmit_DMA(spi, &sendBuf, 1);
		sendBuf = 0;
		HAL_SPI_Transmit_DMA(spi, &sendBuf, 1);
		sendBuf = 0x04;
		HAL_SPI_Transmit_DMA(spi, &sendBuf, 1);
		sendBuf = 0x37;
		HAL_SPI_Transmit_DMA(spi, &sendBuf, 1);
		for (int i = 0; i < 1792; ++i) {
			HAL_SPI_Transmit_DMA(spi, &sendBuf, 1);
		}
		while (HAL_SPI_GetState(spi) == HAL_SPI_STATE_BUSY_TX) {
			__NOP();
		}
		HAL_GPIO_WritePin(GP1287_CS_PORT, GP1287_CS_PIN, GPIO_PIN_SET);
	}
}

