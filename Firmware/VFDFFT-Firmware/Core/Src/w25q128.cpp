#include "w25q128.h"
#include "w25_cmd.h"

static void pollMemoryReadyState(QSPI_HandleTypeDef* qspi, u32 timeout) {
	QSPI_CommandTypeDef command;
	QSPI_AutoPollingTypeDef config;

	command.InstructionMode = QSPI_INSTRUCTION_1_LINE;
	command.Instruction = NORCMD::READ_REG1;
	command.AddressMode = QSPI_ADDRESS_NONE;
	command.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
	command.DataMode = QSPI_DATA_1_LINE;
	command.DummyCycles = 0;
	command.DdrMode = QSPI_DDR_MODE_DISABLE;
	command.DdrHoldHalfCycle = QSPI_DDR_HHC_ANALOG_DELAY;
	command.SIOOMode = QSPI_SIOO_INST_EVERY_CMD;

	config.Match = 0x00;
	config.Mask = NORCMD::REG_STATUS_BUSY;
	config.MatchMode = QSPI_MATCH_MODE_AND;
	config.StatusBytesSize = 1;
	config.Interval = 0x10;
	config.AutomaticStop = QSPI_AUTOMATIC_STOP_ENABLE;

	HAL_QSPI_AutoPolling(qspi, &command, &config, timeout);
}

static void resetMemory(QSPI_HandleTypeDef* qspi) {
	QSPI_CommandTypeDef command;
	command.InstructionMode = QSPI_INSTRUCTION_1_LINE;
	command.Instruction = NORCMD::RESET_ENABLES;
	command.AddressMode = QSPI_ADDRESS_NONE;
	command.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
	command.DataMode = QSPI_DATA_NONE;
	command.DummyCycles = 0;
	command.DdrMode = QSPI_DDR_MODE_DISABLE;
	command.DdrHoldHalfCycle = QSPI_DDR_HHC_ANALOG_DELAY;
	command.SIOOMode = QSPI_SIOO_INST_EVERY_CMD;

	HAL_QSPI_Command(qspi, &command, HAL_QPSI_TIMEOUT_DEFAULT_VALUE);

	command.Instruction = NORCMD::RESET_DEVICE;

	HAL_QSPI_Command(qspi, &command, HAL_QPSI_TIMEOUT_DEFAULT_VALUE);

	pollMemoryReadyState(qspi, HAL_QPSI_TIMEOUT_DEFAULT_VALUE);
}

static void writeEnable(QSPI_HandleTypeDef* qspi) {
	QSPI_CommandTypeDef command;
	QSPI_AutoPollingTypeDef config;

	command.InstructionMode = QSPI_INSTRUCTION_1_LINE;
	command.Instruction = NORCMD::WRITE_ENABLE;
	command.AddressMode = QSPI_ADDRESS_NONE;
	command.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
	command.DataMode = QSPI_DATA_NONE;
	command.DummyCycles = 0;
	command.DdrMode = QSPI_DDR_MODE_DISABLE;
	command.DdrHoldHalfCycle = QSPI_DDR_HHC_ANALOG_DELAY;
	command.SIOOMode = QSPI_SIOO_INST_EVERY_CMD;

	HAL_QSPI_Command(qspi, &command, HAL_QPSI_TIMEOUT_DEFAULT_VALUE);

	config.Match = NORCMD::REG_STATUS_WREN;
	config.Mask = NORCMD::REG_STATUS_WREN;
	config.MatchMode = QSPI_MATCH_MODE_AND;
	config.StatusBytesSize = 1;
	config.Interval = 0x10;
	config.AutomaticStop = QSPI_AUTOMATIC_STOP_ENABLE;

	command.Instruction = NORCMD::READ_REG1;
	command.DataMode = QSPI_DATA_1_LINE;
	command.NbData = 1;

	HAL_QSPI_AutoPolling(qspi, &command, &config, HAL_QPSI_TIMEOUT_DEFAULT_VALUE);
}

u8 readFromW25Q128(QSPI_HandleTypeDef *qspi, u32 addr, u32 size, u8 *buffer) {
	QSPI_CommandTypeDef command;
	command.InstructionMode = QSPI_INSTRUCTION_1_LINE;
	command.Instruction = NORCMD::ENTER_QPI_MODE;
	command.AddressMode = QSPI_ADDRESS_NONE;
	command.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
	command.DataMode = QSPI_DATA_NONE;
	command.DummyCycles = 0;
	command.DdrMode = QSPI_DDR_MODE_DISABLE;
	command.DdrHoldHalfCycle = QSPI_DDR_HHC_ANALOG_DELAY;
	command.SIOOMode = QSPI_SIOO_INST_EVERY_CMD;

	HAL_QSPI_Command(qspi, &command, HAL_QPSI_TIMEOUT_DEFAULT_VALUE);

	command.InstructionMode = QSPI_INSTRUCTION_4_LINES;
	command.Instruction = NORCMD::FAST_READ_DATA;
	command.AddressMode = QSPI_ADDRESS_4_LINES;
	command.AddressSize = QSPI_ADDRESS_24_BITS;
	command.Address = addr;
	command.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
	command.DataMode = QSPI_DATA_4_LINES;
	command.DummyCycles = 2;
	command.NbData = size;
	command.DdrMode = QSPI_DDR_MODE_DISABLE;
	command.DdrHoldHalfCycle = QSPI_DDR_HHC_ANALOG_DELAY;
	command.SIOOMode = QSPI_SIOO_INST_EVERY_CMD;

	HAL_QSPI_Command(qspi, &command, HAL_QPSI_TIMEOUT_DEFAULT_VALUE);

	HAL_QSPI_Receive(qspi, buffer, HAL_QPSI_TIMEOUT_DEFAULT_VALUE);

	command.InstructionMode = QSPI_INSTRUCTION_4_LINES;
	command.Instruction = NORCMD::EXIT_QPI_MODE;
	command.AddressMode = QSPI_ADDRESS_NONE;
	command.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
	command.DataMode = QSPI_DATA_NONE;
	command.DummyCycles = 0;
	command.DdrMode = QSPI_DDR_MODE_DISABLE;
	command.DdrHoldHalfCycle = QSPI_DDR_HHC_ANALOG_DELAY;
	command.SIOOMode = QSPI_SIOO_INST_EVERY_CMD;

	HAL_QSPI_Command(qspi, &command, HAL_QPSI_TIMEOUT_DEFAULT_VALUE);

	return HAL_OK;
}

u8 writeToW25Q128(QSPI_HandleTypeDef *qspi, u32 addr, u32 size, u8 *data) {
	QSPI_CommandTypeDef command;
	u32 endAddr, currSize, ptr = 0;

	while (ptr <= addr) {
		ptr += 0x100;
	}
	currSize = ptr - addr;

	if (currSize > size) {
		currSize = size;
	}

	ptr = addr;
	endAddr = addr + size;

	command.InstructionMode = QSPI_INSTRUCTION_1_LINE;
	command.Instruction = NORCMD::QIN_PAGE_PROGRAM;
	command.AddressMode = QSPI_ADDRESS_1_LINE;
	command.AddressSize = QSPI_ADDRESS_24_BITS;
	command.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
	command.DataMode = QSPI_DATA_4_LINES;
	command.DummyCycles = 0;
	command.DdrMode = QSPI_DDR_MODE_DISABLE;
	command.DdrHoldHalfCycle = QSPI_DDR_HHC_ANALOG_DELAY;
	command.SIOOMode = QSPI_SIOO_INST_EVERY_CMD;

	do {
		command.Address = ptr;
		command.NbData = currSize;

		writeEnable(qspi);
		HAL_QSPI_Command(qspi, &command, HAL_QPSI_TIMEOUT_DEFAULT_VALUE);
		HAL_QSPI_Transmit(qspi, data, HAL_QPSI_TIMEOUT_DEFAULT_VALUE);
		pollMemoryReadyState(qspi, HAL_QPSI_TIMEOUT_DEFAULT_VALUE);

		ptr += currSize;
		data += currSize;
		currSize = ((ptr + 0x100) > endAddr) ? (endAddr - ptr) : 0x100;
	} while (ptr < endAddr);

	return HAL_OK;
}

u8 eraseBlockW25Q128(QSPI_HandleTypeDef *qspi, u32 addr) {
	QSPI_CommandTypeDef command;

	command.InstructionMode = QSPI_INSTRUCTION_1_LINE;
	command.Instruction = NORCMD::ERASE_SECTOR;
	command.AddressMode = QSPI_ADDRESS_1_LINE;
	command.AddressSize = QSPI_ADDRESS_24_BITS;
	command.Address = addr;
	command.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
	command.DataMode = QSPI_DATA_NONE;
	command.DummyCycles = 0;
	command.DdrMode = QSPI_DDR_MODE_DISABLE;
	command.DdrHoldHalfCycle = QSPI_DDR_HHC_ANALOG_DELAY;
	command.SIOOMode = QSPI_SIOO_INST_EVERY_CMD;

	writeEnable(qspi);

	HAL_QSPI_Command(qspi, &command, HAL_QPSI_TIMEOUT_DEFAULT_VALUE);

	pollMemoryReadyState(qspi, 800);
}

u8 eraseChipW25Q128(QSPI_HandleTypeDef *qspi, u32 addr) {
	QSPI_CommandTypeDef command;
	command.InstructionMode = QSPI_INSTRUCTION_1_LINE;
	command.Instruction = NORCMD::ERASE_CHIP;
	command.AddressMode = QSPI_ADDRESS_NONE;
	command.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
	command.DataMode = QSPI_DATA_NONE;
	command.DummyCycles = 0;
	command.DdrMode = QSPI_DDR_MODE_DISABLE;
	command.DdrHoldHalfCycle = QSPI_DDR_HHC_ANALOG_DELAY;
	command.SIOOMode = QSPI_SIOO_INST_EVERY_CMD;

	writeEnable(qspi);
	HAL_QSPI_Command(qspi, &command, HAL_QPSI_TIMEOUT_DEFAULT_VALUE);

	pollMemoryReadyState(qspi, 800);

	return HAL_OK;
}

u8 initW25Q128(QSPI_HandleTypeDef *qspi) {
	QSPI_CommandTypeDef command;
	u8 val = NORCMD::REG_STATUS_QE;

	resetMemory(qspi);
	writeEnable(qspi);

	command.InstructionMode = QSPI_INSTRUCTION_1_LINE;
	command.Instruction = NORCMD::WRITE_REG2;
	command.AddressMode = QSPI_ADDRESS_NONE;
	command.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
	command.DataMode = QSPI_DATA_1_LINE;
	command.DummyCycles = 0;
	command.NbData = 1;
	command.DdrMode = QSPI_DDR_MODE_DISABLE;
	command.DdrHoldHalfCycle = QSPI_DDR_HHC_ANALOG_DELAY;
	command.SIOOMode = QSPI_SIOO_INST_EVERY_CMD;

	HAL_QSPI_Command(qspi, &command, HAL_QPSI_TIMEOUT_DEFAULT_VALUE);

	pollMemoryReadyState(qspi, 800);

	return HAL_OK;
}

