#ifndef __MODULE_SELECT_H__
#define __MODULE_SELECT_H__

#ifdef __cplusplus
extern "C" {
#endif
//设置RGB型号
/* LBX_1250B_C_V12
 * LBX_1250B_C_D_V11
 *
 *
 */

#ifndef RGB_FIXTRUE
#define RGB_FIXTRUE  1
#define _W25QXX_DEBUG                 0
#define _W25QXX_DEBUG_Write     0
#define _W25QXX_DEBUG_Read     1
#define _W25QXX_USE_DMA 	      1
#endif
#ifndef LBX_1250B_C_D_V11
#define LBX_1250B_C_D_V11
#endif




#ifdef LBX_1250A_C_V11
#define ONE_PULSE        (154)                           //1 码
#define ZERO_PULSE       (66)                           //0 码
#define RESET_PULSE      (180)                           //80 ，复位信号
#define LED_NUMS         (72)                          //led 数量
#define LED_DATA_LEN     (24)                           //led 长度，单个需要24bits
#define WS2812_DATA_LEN  (LED_NUMS*LED_DATA_LEN)        //ws2812灯条需要的数组长度
#define VALTAGE_MIN 3.000
#define VALTAGE_MAX 6.000
#define CURRENT_MIN 110.000
#define CURRENT_MAX 130.000
#define PULSE_DOUT 3
#endif
#ifdef LBX_1250B_C_D_V11
#define ONE_PULSE        (150)                           //1 码
#define ZERO_PULSE       (50)                           //0 码
#define RESET_PULSE      (180)                           //80 ，复位信号
#define LED_NUMS         (120)                          //led 数量
#define LED_DATA_LEN     (24)                           //led 长度，单个需要24bits
#define WS2812_DATA_LEN  (LED_NUMS*LED_DATA_LEN)        //ws2812灯条需要的数组长度
#define VALTAGE_MIN 3.000
#define VALTAGE_MAX 6.000
#define CURRENT_MIN 150.000
#define CURRENT_MAX 215.000
#define PULSE_DOUT 3
#endif

#ifdef LBX_1250B_C_V12
#define  LBX_1250B_E_V12
#define ONE_PULSE        (150)                           //1 码
#define ZERO_PULSE       (70)                           //0 码
#define RESET_PULSE      (180)                           //80 ，复位信号
#define LED_NUMS         (60)                          //led 数量
#define LED_DATA_LEN     (24)                           //led 长度，单个需要24bits
#define WS2812_DATA_LEN  (LED_NUMS*LED_DATA_LEN)        //ws2812灯条需要的数组长度
#define VALTAGE_MIN 3.000
#define VALTAGE_MAX 6.000
#define CURRENT_MIN 90.000
#define CURRENT_MAX 110.000
#define PULSE_DOUT 3
#endif

#ifdef LBX_1250B_F_V12
#define ONE_PULSE        (150)                           //1 码
#define ZERO_PULSE       (70)                           //0 码
#define RESET_PULSE      (180)                           //80 ，复位信号
#define LED_NUMS         (40)                          //led 数量
#define LED_DATA_LEN     (24)                           //led 长度，单个需要24bits
#define WS2812_DATA_LEN  (LED_NUMS*LED_DATA_LEN)        //ws2812灯条需要的数组长度
#define VALTAGE_MIN 3.000
#define VALTAGE_MAX 6.000
#define CURRENT_MIN 60.000
#define CURRENT_MAX 80.000
#define PULSE_DOUT 3
#endif

#ifdef LBX_1250C_B_V12
#define ONE_PULSE        (150)                           //1 码
#define ZERO_PULSE       (50)                           //0 码
#define RESET_PULSE      (180)                           //80 ，复位信号
#define LED_NUMS         (120)                          //led 数量
#define LED_DATA_LEN     (24)                           //led 长度，单个需要24bits
#define WS2812_DATA_LEN  (LED_NUMS*LED_DATA_LEN)        //ws2812灯条需要的数组长度
#define VALTAGE_MIN 3.000
#define VALTAGE_MAX 6.000
#define CURRENT_MIN 150.000
#define CURRENT_MAX 215.000
#define PULSE_DOUT 3
#endif

#ifdef __cplusplus
}
#endif

#endif
