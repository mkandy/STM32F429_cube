#include "bosmfc.h"
#include "cmsis_os.h"
/*
*
ONE_PULSE	ZERO_PULSE	WS2812_DATA_LEN
149	74	334
149 =（224+1）* 2/3	74 = （224+1）* 2/3	80 + led_nums * 24
*
*/


uint32_t static RGB_buffur[RESET_PULSE + WS2812_DATA_LEN]={0} ;

void ws2812_set_RGB(uint8_t R, uint8_t G, uint8_t B, uint16_t num)
{
    //
	uint32_t* p = (RGB_buffur + RESET_PULSE) + (num * LED_DATA_LEN);

    for (uint16_t i = 0;i < 8;i++)
    {
        //
        p[i]      = (G << i) & (0x80)?ONE_PULSE:ZERO_PULSE;
        p[i + 8]  = (R << i) & (0x80)?ONE_PULSE:ZERO_PULSE;
        p[i + 16] = (B << i) & (0x80)?ONE_PULSE:ZERO_PULSE;

    }
}
/*ws2812 初始化*/
void ws2812_init(uint8_t led_nums)
{
	  //Dout——PWM捕获端初始化；
	//__HAL_TIM_SET_CAPTUREPOLARITY(&htim3,TIM_CHANNEL_1,TIM_INPUTCHANNELPOLARITY_RISING);  //设置为下降沿捕获
	//HAL_TIM_IC_Start_IT(&htim3,	TIM_CHANNEL_1);  //开启输入中断
	HAL_TIM_Base_Start(&htim2);
	for(uint8_t i = 0; i < led_nums; i++)
	{
		ws2812_set_RGB(0x00, 0x00, 0x00, i);
	}
	 HAL_TIM_PWM_Start_DMA(&htim8,TIM_CHANNEL_2,RGB_buffur,RESET_PULSE + WS2812_DATA_LEN);
}
/*全亮蓝灯*/
void ws2812_blue(uint8_t led_nums)
{
	for(uint8_t i = 0; i < led_nums; i++)
	{
		ws2812_set_RGB(0x00, 0x00, 0x22, i);
	}
	 HAL_TIM_PWM_Start_DMA(&htim8,TIM_CHANNEL_2,RGB_buffur,RESET_PULSE + WS2812_DATA_LEN);
}
/*全亮红灯*/
void ws2812_red(uint8_t led_nums)
{
	for(uint8_t i = 0; i < led_nums; i++)
	{
		ws2812_set_RGB(0x22, 0x00, 0x00, i);
	}
	 HAL_TIM_PWM_Start_DMA(&htim8,TIM_CHANNEL_2,RGB_buffur,RESET_PULSE + WS2812_DATA_LEN);
}
/*全亮绿灯*/
void ws2812_green(uint8_t led_nums)
{
	for(uint8_t i = 0; i < led_nums; i++)
	{
		ws2812_set_RGB(0x00, 0x22, 0x00, i);
	}
	 HAL_TIM_PWM_Start_DMA(&htim8,TIM_CHANNEL_2,RGB_buffur,RESET_PULSE + WS2812_DATA_LEN);
}
uint8_t pulse=0;
void ws2812_example(void)
{		

    //#2.传输数据
    ws2812_red(LED_NUMS);
    rgbset.R=1;
    osDelay(400);

    //#3.延时：使效果可以被观察
    ws2812_green(LED_NUMS);
    rgbset.G=1;
    osDelay(400);

   //#1.填充数组
	ws2812_blue(LED_NUMS);
	rgbset.B=1;

	pulse=htim2.Instance->CNT;
	htim2.Instance->CNT=0;
	 osDelay(400);
}

