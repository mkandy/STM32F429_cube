#ifndef	_AT24C16_H
#define	_AT24C16_H
#include "stdint.h"
#ifdef __cplusplus
 extern "C" {
#endif
#define E2PROM_SIZE 0x0800    //0x0800=2k byte=16K bit
#define E2PROM_BASE_ID    0xA0//address_ID
#define E2PROM_WRITE 0x00//Write_flag
#define E2PROM_READ     0x01//Read_flag
#define EEPROMBufferSize   2000 //2K number size
#define E2PROM_BASE_WID E2PROM_BASE_ID + E2PROM_WRITE
#define E2PROM_BASE_RID E2PROM_BASE_ID + E2PROM_READ
#define E2PROM_PAGE_MASK    0x000F//page=0-15=0x000f
void vE2romTest(void);
uint8_t writeAT24C16(uint16_t addr, uint8_t *data, uint16_t len);
uint8_t readAT24C16(uint16_t addr, uint8_t *data, uint16_t len);
//############################################################################
#ifdef __cplusplus
}
#endif

#endif

/* EOF */
