#ifndef  WS2812B_H
#define WS2812B_H
#include "type.h"
#include "stdint.h"
#include "tim.h"
#include "module_select.h"



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
