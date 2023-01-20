#ifndef VFDFFT_FIRMWARE_LOGGING_H
#define VFDFFT_FIRMWARE_LOGGING_H

#include <string>
#include "stm32f4xx.h"
namespace LoggingValues {
	typedef enum LogLevel {
		DEBUG,
		INFO,
		WARN,
		ERROR,
		FATAL
	} LogLevel;

	typedef enum Module {
		MAIN,
		DAC_,
		DMA,
		ES9023,
		GP1287BI,
		GPIO,
		HDC1080,
		OPT3001,
		W25Q128,
		AP6181,
		USB,
		UART
	} Module;
}

void log(UART_HandleTypeDef* uart, LoggingValues::LogLevel level, LoggingValues::Module module, std::string message);

#endif //VFDFFT_FIRMWARE_LOGGING_H
