#include "logging.h"
#include "stm32f4xx.h"
void log(UART_HandleTypeDef* uart, LoggingValues::LogLevel level, LoggingValues::Module module, const std::string& message) {
	std::string str;
	str += level == LoggingValues::DEBUG ? "[DEBUG]" : level == LoggingValues::INFO ? "[INFO]" : level == LoggingValues::WARN ? "[WARN]" : level == LoggingValues::ERROR ? "[ERROR]" : "[FATAL]";
	str += " ";
	switch (module) {
		case LoggingValues::MAIN:
			str += "[MAIN]";
			break;
		case LoggingValues::DAC_:
			str += "[DAC]";
			break;
		case LoggingValues::DMA:
			str += "[DMA]";
			break;
		case LoggingValues::ES9023:
			str += "[ES9023]";
			break;
		case LoggingValues::GP1287BI:
			str += "[GP1287BI]";
			break;
		case LoggingValues::GPIO:
			str += "[GPIO]";
			break;
		case LoggingValues::HDC1080:
			str += "[HDC1080]";
			break;
		case LoggingValues::OPT3001:
			str += "[OPT3001]";
			break;
		case LoggingValues::W25Q128:
			str += "[W25Q128]";
			break;
		case LoggingValues::AP6181:
			str += "[AP6181]";
			break;
		case LoggingValues::USB:
			str += "[USB]";
			break;
		case LoggingValues::UART:
			str += "[UART]";
			break;
		default:
			break;
	}

	str += " ";
	str += message;
	str += "\n";

	for (const auto &item: str) {
		HAL_UART_Transmit(uart, (uint8_t*)((void*)(&item)), 1, 0xFFFF);
	}
}
