#ifndef VFDFFT_FIRMWARE_GP1287BI_H
#define VFDFFT_FIRMWARE_GP1287BI_H

#include <cstdarg>
#include "stm32f4xx.h"
#include "types.h"

void sendCommandToGP1287BI(SPI_HandleTypeDef* spi, u8 total, ...);
void writeDisplayDataToGP1287BI(SPI_HandleTypeDef* spi, u8 x, u8 y, u8 yLength, const u8* data, u16 size);
void initGP1287BI(SPI_HandleTypeDef* spi);
void clearGP1287BI(SPI_HandleTypeDef* spi, u8 color);


#endif //VFDFFT_FIRMWARE_GP1287BI_H
