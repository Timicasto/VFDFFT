#ifndef VFDFFT_FIRMWARE_ES9023_H
#define VFDFFT_FIRMWARE_ES9023_H

#include "stm32f4xx.h"
#include "types.h"

void es9023Play(I2S_HandleTypeDef* i2s, u16* bufAddr);

#endif //VFDFFT_FIRMWARE_ES9023_H
