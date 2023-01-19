#ifndef VFDFFT_FIRMWARE_W25_CMD_H
#define VFDFFT_FIRMWARE_W25_CMD_H

#include "types.h"

namespace NORCMD {

	static const u8 RESET_ENABLES = 0x66;
	static const u8 RESET_DEVICE = 0x99;

	static const u8 ENTER_QPI_MODE = 0x38;
	static const u8 EXIT_QPI_MODE = 0xFF;

	static const u8 READ_DEVID = 0x90;
	static const u8 READ_DEVID_DSPI = 0x92;
	static const u8 READ_DEVID_QSPI = 0x94;
	static const u8 READ_JEDEC_ID = 0x9F;

	static const u8 READ_DATA = 0x03;
	static const u8 FAST_READ_DATA = 0x0B;
	static const u8 FAST_READ_DO = 0x3B;
	static const u8 FAST_READ_DIO = 0xBB;
	static const u8 FAST_READ_QO = 0x6B;
	static const u8 FAST_READ_QIO = 0xEB;

	static const u8 READ_REG1 = 0x05;
	static const u8 READ_REG2 = 0x35;
	static const u8 READ_REG3 = 0x15;
	static const u8 WRITE_REG1 = 0x01;
	static const u8 WRITE_REG2 = 0x31;
	static const u8 WRITE_REG3 = 0x11;

	static const u8 PAGE_PROGRAM = 0x02;
	static const u8 QIN_PAGE_PROGRAM = 0x32;

	static const u8 ERASE_SECTOR = 0x20; // 4KB
	static const u8 ERASE_BLOCK_32 = 0x52; // 32KB
	static const u8 ERASE_BLOCK_64 = 0xD8; // 64KB
	static const u8 ERASE_CHIP = 0xC7;

	static const u8 SUSPEND_ERASE = 0x75;
	static const u8 RESUME_ERASE = 0x7A;

}

#endif //VFDFFT_FIRMWARE_W25_CMD_H
