#ifndef _W25QXXCONFIG_H
#define _W25QXXCONFIG_H
#include "spi.h"
#include "stm32f4xx_hal_conf.h"// set USE_HAL_SPI_REGISTER_CALLBACKS 1u in "stm32f4xx_hal_conf.h"

#define _W25QXX_SPI                   hspi2
#define _W25QXX_CS_GPIO               FLASH_CS_GPIO_Port
#define _W25QXX_CS_PIN                FLASH_CS_Pin
#define _W25QXX_USE_FREERTOS          0
#define _W25QXX_DEBUG                 0
#define _W25QXX_USE_DMA 	      1
#endif

