#ifndef  WS2812B_H
#define WS2812B_H
#include "type.h"
#include "stdint.h"
#include "tim.h"
#define ONE_PULSE        (154)                           //1 码
#define ZERO_PULSE       (66)                           //0 码
#define RESET_PULSE      (280)                           //80 ，复位信号
#define LED_NUMS         120                            //led 数量
#define LED_DATA_LEN     (24)                           //led 长度，单个需要24bits
#define WS2812_DATA_LEN  (LED_NUMS*LED_DATA_LEN)        //ws2812灯条需要的数组长度



typedef struct
{
uint8_t  R :2;
uint8_t G :2;
uint8_t B :2;
}rgb;
rgb rgbset;
void ws2812_set_RGB(uint8_t R, uint8_t G, uint8_t B, uint16_t num);
void ws2812_init(uint8_t led_nums);
void ws2812_example(void);
extern void ws2812_blue(uint8_t led_nums);
extern void ws2812_red(uint8_t led_nums);
extern void ws2812_green(uint8_t led_nums);
void DetectRgb_Dout(void);
#endif
