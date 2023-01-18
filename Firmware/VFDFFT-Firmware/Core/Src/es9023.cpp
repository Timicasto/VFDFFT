#include "es9023.h"

void es9023Play(I2S_HandleTypeDef *i2s, u32 *bufAddr) {
	HAL_I2S_Transmit_DMA(i2s, reinterpret_cast<uint16_t *>(bufAddr), 2);
}
