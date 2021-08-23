#include "at24c16.h"
#include "i2c.h"


uint8_t writeAT24C16(uint16_t addr, uint8_t *data, uint16_t len)
{
    uint8_t wNum = 0;
    uint16_t lenLeft = len;
    uint8_t deviceId ;
    uint8_t *p = data;

    /*is the address overfolw*/
    if(addr + len >= E2PROM_SIZE)
        return 1;

    /*calculate the current write position to know how many word can write continully*/
    wNum = 16 - (addr & E2PROM_PAGE_MASK);
    if(wNum == 0)
        wNum = 16;
    wNum = lenLeft>=wNum ? wNum : lenLeft;

    /*transmit the date to e2prom*/
    while(lenLeft)
    {
        /*calculate the device id*/
        deviceId = (addr >> 8)<=0 ?  E2PROM_BASE_WID :( (E2PROM_BASE_WID )| (uint8_t)((addr>>7)&0x0E));

        if( HAL_I2C_Mem_Write(&hi2c1, deviceId, addr&0x00FF,
                              I2C_MEMADD_SIZE_8BIT, p, wNum, 0x20) != HAL_OK)
        {
            printf("I2S Write error!\r\n");
            HAL_Delay(5);
            continue;
        }
        addr += wNum;
        lenLeft -= wNum;
        p += wNum;
        wNum = lenLeft > 16 ? 16 : lenLeft;

        HAL_Delay(5);
    }

    return HAL_OK;
}

uint8_t readAT24C16(uint16_t addr, uint8_t *data, uint16_t len)
{
    uint8_t rNum = 0;
    uint16_t lenLeft = len;
    uint8_t deviceId ;
    uint8_t *p = data;

    /*is the address overfolw*/
    if(addr + len >= E2PROM_SIZE)
        return 1;

    /*calculate the current write position to know how many word can write continully*/
    rNum = 16 - (addr & E2PROM_PAGE_MASK);
    if(rNum == 0)
    {  rNum = 16; printf("I2S rNum error!\r\n");}
    rNum = lenLeft>=rNum ? rNum : lenLeft;
    printf("\r\ndevice_rNum:%d\r\n",rNum);
    /*transmit the date to e2prom*/
    while(lenLeft)
    {
        /*calculate the device id*/
        deviceId = (addr >> 8)<=0 ?  E2PROM_BASE_RID : ((E2PROM_BASE_RID) | (uint8_t)((addr>>7)&0x0E));

        if( HAL_I2C_Mem_Read(&hi2c1, deviceId, addr&0x00FF,
                            I2C_MEMADD_SIZE_8BIT, p, rNum, 20) != HAL_OK)
        {
            printf("I2S Read error!\r\n");
            continue;
        }
        addr += rNum;
        lenLeft -= rNum;
        p += rNum;
        rNum = lenLeft > 16 ? 16 : lenLeft;
    }

    return HAL_OK;
}
uint8_t WriteBuffer[EEPROMBufferSize],ReadBuffer[EEPROMBufferSize];
uint8_t i;
void vE2romTest(void)
{


    printf("\r\n***************I2C Example*******************************\r\n");
    for(i=0; i<50; i++)
{
    WriteBuffer[i]=i;    /* WriteBuffer init */
    printf("EEPROM 24C16 Write:%d\r\n  ",WriteBuffer[i]);
    	}
    /* wrinte date to EEPROM */
    if(!writeAT24C16(0x05,WriteBuffer,EEPROMBufferSize))
            printf("\r\n EEPROM 24C16 Write Test OK \r\n");
    else
            printf("\r\n EEPROM 24C16 Write Test False \r\n");

    /* read date from EEPROM */
    if( !readAT24C16(0x05,ReadBuffer, EEPROMBufferSize) ) /* check date */
        printf("\r\n EEPROM 24C16 Read Test OK\r\n");
        else
        printf("\r\n EEPROM 24C16 Read Test False\r\n");
    for(i=0; i<50; i++)
        printf("EEPROM 24C16 Read:%d\r\n  ",ReadBuffer[i]);


}
