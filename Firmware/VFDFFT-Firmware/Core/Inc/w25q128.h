#ifndef VFDFFT_FIRMWARE_W25Q128_H
#define VFDFFT_FIRMWARE_W25Q128_H

#include <vector>
#include "stm32f4xx.h"
#include "types.h"

u8 readFromW25Q128(u32 addr, u32 size, u8* buffer);
u8 writeToW25Q128(u32 addr, u32 size, u8 data[]);
u8 eraseBlockW25Q128(u32 addr);
u8 eraseChipW25Q128(u32 addr);
u8 initW25Q128();

#endif //VFDFFT_FIRMWARE_W25Q128_H
