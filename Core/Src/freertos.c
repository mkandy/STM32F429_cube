/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "lwip/opt.h"
#include "lwip/sys.h"
#include "lwip/api.h"
#include "lwip/sockets.h"
#include "string.h"

 #include <stdio.h>
#include "DS_INA226.h"
#include "w25qxx.h"
#include "at24c16.h"
#include "lcd.h"
#include "bosmfc.h"

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define PORT   5001
#define IP_ADDR  "192.168.3.100"
#define RECV_DATA 256
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */
#ifndef LOGO_W
#define LOGO_W	480
#endif
#ifndef LOGO_H
#define LOGO_H	799
#endif

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */

/* USER CODE END Variables */
/* Definitions for defaultTask */
osThreadId_t defaultTaskHandle;
const osThreadAttr_t defaultTask_attributes = {
  .name = "defaultTask",
  .stack_size = 1024 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for PingTask */
osThreadId_t PingTaskHandle;
const osThreadAttr_t PingTask_attributes = {
  .name = "PingTask",
  .stack_size = 1024 * 4,
  .priority = (osPriority_t) osPriorityLow,
};
/* Definitions for UartTask */
osThreadId_t UartTaskHandle;
const osThreadAttr_t UartTask_attributes = {
  .name = "UartTask",
  .stack_size = 1024 * 4,
  .priority = (osPriority_t) osPriorityLow,
};
/* Definitions for Flash_w25q */
osThreadId_t Flash_w25qHandle;
const osThreadAttr_t Flash_w25q_attributes = {
  .name = "Flash_w25q",
  .stack_size = 1024 * 4,
  .priority = (osPriority_t) osPriorityLow,
};
/* Definitions for AT24C16Start */
osThreadId_t AT24C16StartHandle;
const osThreadAttr_t AT24C16Start_attributes = {
  .name = "AT24C16Start",
  .stack_size = 1024 * 4,
  .priority = (osPriority_t) osPriorityLow,
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */
void client(void);


/* USER CODE END FunctionPrototypes */

void StartDefaultTask(void *argument);
void StartPingTask(void *argument);
void StartUartTask(void *argument);
void StartFlash_w25q(void *argument);
void StartAT24C16Start(void *argument);

extern void MX_LWIP_Init(void);
void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */

void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */
	LCD_Init();					//初始化LCD
	LCD_Display_Dir(0);//竖屏显示刷背�?????
	W25qxx_Init();
#if (_W25QXX_DEBUG_Read==1)
	  uint16_t i,j;
	  uint8_t rBuff[2]="";
	  uint32_t rnumber=0;
	  for(i=0;i<LOGO_H;i++)
		  {
			LCD_SetCursor(0,i);   	//设置光标位置
			LCD_WriteRAM_Prepare();     //�???????????????????????????????始写入GRAM
				for(j=0;j<LOGO_W;j++)
				{

					//LCD->LCD_RAM=sky_animation_mask[i*799+j];
			/*		image=i*799+j;
				// printf("\r\n>>>>>>sky_animation_mask= 0x%hx\r\n",sky_animation_mask[image]);
				 printf("\r\n\r\n\r\nimage %d\r\n",(int)image);

				 wBuff[0] = sky_animation_mask[image];
				 wBuff[1] = (sky_animation_mask[image]>>8);
		 // printf("\r\n wBuffL= 0x%x  wBuffH= 0x%x\r\n",wBuff[0],wBuff[1]);

		  W25qxx_WriteByte(wBuff[0],rnumber);
		  W25qxx_WriteByte(wBuff[1],rnumber+1);
		  */
		  W25qxx_ReadByte(&rBuff[0],rnumber);
		  W25qxx_ReadByte(&rBuff[1],rnumber+1);
			// printf(" rBuffL=%x rBuffH= 0x%x \r\n",rBuff[0],rBuff[1]);
		  uint16_t readflash16hex;
		  readflash16hex=rBuff[1];
		  readflash16hex=((readflash16hex<<8)+rBuff[0]);
		  LCD->LCD_RAM=readflash16hex;
		//	 printf("\r\nrnumber %d\r\n",rnumber);
		//	 printf("\r\n>>>>>>readflash16hex= 0x%hx\r\n",readflash16hex);

			 rnumber=rnumber+2;

				}
		  }

#elif(_W25QXX_DEBUG_Write==0)
  LCD_Color_Fill(1,1,LOGO_W,LOGO_H,(uint16_t*)sky_animation_mask); //指定区域填充色块（color为色块数组）
//  LCD_ShowString(250,240,200,32,32,"DS STM32F4/F7",1);
#endif
  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */

  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* creation of defaultTask */
  defaultTaskHandle = osThreadNew(StartDefaultTask, NULL, &defaultTask_attributes);

  /* creation of PingTask */
  PingTaskHandle = osThreadNew(StartPingTask, NULL, &PingTask_attributes);

  /* creation of UartTask */
  UartTaskHandle = osThreadNew(StartUartTask, NULL, &UartTask_attributes);

  /* creation of Flash_w25q */
  Flash_w25qHandle = osThreadNew(StartFlash_w25q, NULL, &Flash_w25q_attributes);

  /* creation of AT24C16Start */
  AT24C16StartHandle = osThreadNew(StartAT24C16Start, NULL, &AT24C16Start_attributes);

  /* USER CODE BEGIN RTOS_THREADS */

  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_EVENTS */
  /* add events, ... */
  /* USER CODE END RTOS_EVENTS */

}

/* USER CODE BEGIN Header_StartDefaultTask */
/**
  * @brief  Function implementing the defaultTask thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void *argument)
{
  /* init code for LWIP */
  MX_LWIP_Init();
  /* USER CODE BEGIN StartDefaultTask */
  /* USER CODE BEGIN 5 */
    /* Infinite loop */
  	int sock = -1, connected;
  	char *recv_data;
  	struct sockaddr_in server_addr, client_addr;
  	socklen_t sin_size;
  	int recv_data_len;

  	recv_data = (char *)pvPortMalloc(RECV_DATA);
  	if(recv_data == NULL)
  	{
  		printf("No memory\n");
  		goto __exit;
  	}

  	sock = socket(AF_INET, SOCK_STREAM, 0);
  	if(sock < 0)
  	{
  		printf("socket error\n");
  	}
  	server_addr.sin_family = AF_INET;
  	server_addr.sin_addr.s_addr = INADDR_ANY;
  	server_addr.sin_port = htons(PORT);
  	memset(&(server_addr.sin_zero), 0, sizeof(server_addr.sin_zero));

  	if(bind(sock, (struct sockaddr *)&server_addr, sizeof(struct sockaddr)) == -1)
  	{
  		printf("unable to bind\n");
  		goto __exit;
  	}

  	listen(sock, 5);

  	while(1)
  	{

  		sin_size = sizeof(struct sockaddr_in);
  		connected = accept(sock, (struct sockaddr *)&client_addr, &sin_size);
  		printf("new client connected from %s, %d\r\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));

  			int flag = 1;
  			setsockopt(connected, IPPROTO_TCP, TCP_NODELAY, (void *)&flag, sizeof(int));

  		while(1)
  		{
  			recv_data_len = recv(connected, recv_data, RECV_DATA, 0);

  			if(recv_data_len <= 0)
  				break;
  			printf("recv %d len data\r\n", recv_data_len);
  			write(connected, recv_data, recv_data_len);
  		}
  		if(connected >= 0)
  			closesocket(connected);
  		connected = -1;
  	}

  __exit:
  	if(recv_data) free(recv_data);
  	if(sock >= 0)  closesocket(sock);

  	vTaskDelete(defaultTaskHandle);
    /* USER CODE END 5 */
  /* USER CODE END StartDefaultTask */
}

/* USER CODE BEGIN Header_StartPingTask */
/**
* @brief Function implementing the PingTask thread.
* @param argument: Not used
* @retval None
*/
uint8_t RGBvalve[]="",RGB_current[]="";
float val_float;
float current_float;
/* USER CODE END Header_StartPingTask */
void StartPingTask(void *argument)
{
  /* USER CODE BEGIN StartPingTask */
	  /* Infinite loop */
	extern I2C_HandleTypeDef hi2c1;


	INA226_setConfig(&hi2c1, INA226_ADDRESS, INA226_MODE_CONT_SHUNT_AND_BUS | INA226_VBUS_140uS | INA226_VBUS_140uS | INA226_AVG_1024);
	INA226_setCalibrationReg(&hi2c1, INA226_ADDRESS, INA226_CALIB_VAL);
	/*SY6288 enable*/
	HAL_GPIO_WritePin(USB_EN_GPIO_Port, USB_EN_Pin, GPIO_PIN_RESET);//closed USB—�?�VBUS1电源
	HAL_GPIO_WritePin(USB_POWER1_GPIO_Port, USB_POWER1_Pin, GPIO_PIN_SET);//打开USB—�?�VBUS2电源
	  for(;;)
	  {
		  val_float= INA226_getBusV(&hi2c1, INA226_ADDRESS);
		  val_float=(val_float*1.25/1000);
		  sprintf(RGBvalve, "%3f", val_float);
		  printf(RGBvalve);
		  current_float=INA226_getCurrent(&hi2c1, INA226_ADDRESS);
		  current_float=(current_float*0.02);
		  sprintf(RGB_current, "%3f", current_float);
		  printf(RGB_current);

	   osDelay(100);
	  }
  /* USER CODE END StartPingTask */
}

/* USER CODE BEGIN Header_StartUartTask */
/**
* @brief Function implementing the UartTask thread.
* @param argument: Not used
* @retval None
*/

/* USER CODE END Header_StartUartTask */
void StartUartTask(void *argument)
{
  /* USER CODE BEGIN StartUartTask */
  /* Infinite loop */


	//	lcdtest();
  for(;;)
  {

	  //client();
	  printf("StartLCDTask\r\n");
    osDelay(100);
  }
  /* USER CODE END StartUartTask */
}

/* USER CODE BEGIN Header_StartFlash_w25q */
/**
* @brief Function implementing the Flash_w25q thread.
* @param argument: Not used
* @retval None
*/



/* USER CODE END Header_StartFlash_w25q */
void StartFlash_w25q(void *argument)
{
  /* USER CODE BEGIN StartFlash_w25q */
	// W25qxx_Init();

	 // W25qxx_EraseSector(0);// erase page 0~15;

	 printf("\r\n note:w25qxx EraseSector_page_is_0-15\r\n");

	  //write the picture into the extern flash

#if (_W25QXX_DEBUG_Write==1)
		 W25qxx_EraseChip();
	 uint16_t i,j;
	 uint8_t wBuff[2]="";
	 uint32_t image,rnumber=0;
	  for(i=0;i<LOGO_H;i++)
	  {
			for(j=0;j<LOGO_W;j++)
			{
//LCD->LCD_RAM=sky_animation_mask[i*LOGO_W+j];

				image=i*LOGO_W+j;
		//	 printf("\r\n>>>>>>sky_animation_mask= 0x%hx\r\n",sky_animation_mask[image]);
		//	 printf("\r\n\r\n\r\nimage %d\r\n",(int)image);
			// printf("\r\nrnumber %d\r\n",rnumber);
			 wBuff[0] = sky_animation_mask[image];
			 wBuff[1] = (sky_animation_mask[image]>>8);
	 printf("\r\nrnumber %d\r\n",rnumber);
	//  printf("\r\n wBuffL= 0x%x  wBuffH= 0x%x\r\n",wBuff[0],wBuff[1]);

	  W25qxx_WriteByte(wBuff[0],rnumber);
	  W25qxx_WriteByte(wBuff[1],rnumber+1);
/*
	  W25qxx_ReadByte(&rBuff[0],rnumber);
	  W25qxx_ReadByte(&rBuff[1],rnumber+1);
		// printf(" rBuffL=%x rBuffH= 0x%x \r\n",rBuff[0],rBuff[1]);
		 readflash16hex=rBuff[1];
		readflash16hex=((readflash16hex<<8)+rBuff[0]);
	LCD->LCD_RAM=readflash16hex;

	  printf("\r\n>>>>>>readflash16hex= 0x%hx\r\n",readflash16hex);
	  */
		 rnumber=rnumber+2;

			}
	  }

#endif
printf("\r\n >>>>>:w25qxx Write_done 0-15\r\n");
  /* Infinite loop */
  for(;;)
  {



	  printf("\r\n >>>>>:w25qxx Write_done 0-15\r\n");
	//  vW25qx_Read(rBuff,0,66530);
	//  printf("\r\nlooprBuff=%x\r\\n",rBuff);
    osDelay(1000);
  }
  /* USER CODE END StartFlash_w25q */
}

/* USER CODE BEGIN Header_StartAT24C16Start */
/**
* @brief Function implementing the AT24C16Start thread.
* @param argument: Not used
* @retval None
*/
extern uint8_t pulse;
uint8_t resultflag;

/* USER CODE END Header_StartAT24C16Start */
void StartAT24C16Start(void *argument)
{
  /* USER CODE BEGIN StartAT24C16Start */
  /* Infinite loop */
ws2812_init(LED_NUMS);//5050串行通讯时序要求很严，注意供电电源，必须稳定，不然无法点�????????????????5050LED
  for(;;)
  {

if((current_float>10)||(RGB_FIXTRUE==1))
{

ws2812_example();
//item 1 display
if( rgbset.R==1)
#ifdef LBX_1250B_C_V12
#elif defined  LBX_1250B_E_V12
	LCD_ShowString(170,87,200,16,16,">set_6*10_R>>>>",1);
#elif defined LBX_1250B_C_D_V11
LCD_ShowString(170,87,200,16,16,">set_4*30_R>>>>",1);
#elif defined LBX_1250A_C_V11
LCD_ShowString(170,87,200,16,16,">set_12*6_R>>>>",1);
#elif defined LBX_1250B_F_V12
LCD_ShowString(170,87,200,16,16,">set_4*10_R>>>>",1);
#elif defined LBX_1250C_B_V12
LCD_ShowString(170,87,200,16,16,">set_20*6_R>>>>",1);
#endif
else LCD_ShowString(170,87,150,16,16,">no_R_led_input",1);
if (rgbset.G==1)
#ifdef LBX_1250B_C_V12
#elif defined  LBX_1250B_E_V12
	LCD_ShowString(170,126,200,16,16,">set_6*10_G>>>>",1);
#elif defined LBX_1250B_C_D_V11
	LCD_ShowString(170,126,200,16,16,">set_4*30_G>>>>",1);
#elif defined LBX_1250A_C_V11
	LCD_ShowString(170,126,200,16,16,">set_12*6_G>>>>",1);
#elif defined LBX_1250B_F_V12
	LCD_ShowString(170,126,200,16,16,">set_4*10_G>>>>",1);
#elif defined LBX_1250C_B_V12
	LCD_ShowString(170,126,200,16,16,">set_20*6_G>>>>",1);
#endif
else LCD_ShowString(170,126,150,16,16,">no_G_led_input",1);
if (rgbset.B==1)
#ifdef LBX_1250B_C_V12
#elif defined  LBX_1250B_E_V12
	LCD_ShowString(170,167,200,16,16,">set_6*10_B>>>>",1);
#elif defined LBX_1250B_C_D_V11
	LCD_ShowString(170,167,200,16,16,">set_4*30_B>>>>",1);
#elif defined LBX_1250A_C_V11
	LCD_ShowString(170,167,200,16,16,">set_12*6_B>>>>",1);
#elif defined LBX_1250B_F_V12
	LCD_ShowString(170,167,200,16,16,">set_4*10_B>>>>",1);
#elif defined LBX_1250C_B_V12
	LCD_ShowString(170,167,200,16,16,">set_20*6_B>>>>",1);
#endif
else LCD_ShowString(170,167,150,16,16,">no_B_led_input",1);
// item 2 display
LCD_ShowString(180,287,60,24,24,RGBvalve,1);
LCD_ShowString(180,329,60,24,24,RGB_current,1);

if(((VALTAGE_MIN<((uint8_t)val_float))&&((uint8_t)val_float)<VALTAGE_MAX)) LCD_ShowString(373,287,60,24,24,"PASS",1);
else LCD_ShowString(373,287,60,24,24,"FAIL",1);

if(((CURRENT_MIN<(uint8_t)current_float)&&((uint8_t)current_float)<CURRENT_MAX)) LCD_ShowString(373,328,60,24,24,"PASS",1);
else LCD_ShowString(373,328,60,24,24,"FAIL",1);

resultflag++;
if(	resultflag==1)
{
LCD_ShowBigString(156,566,400,148,148,"%&'(",BIGWORD_ClEARCOLOR,1);//注意这里是用字符代替显示内容，因为flash不够无需导入多余的字符显示，真正的数据为"FAILED"对应的数据标�?????
//for(uint8_t i=40;i<50;i++)
LCD_Draw_Circle(270,650,50);

}
if(	resultflag>=3)//delay(1S) Display result time for reset testing;
{resultflag=0;
//item 3display
uint8_t pulsenumber[1]="0";
sprintf(pulsenumber, "%2d", pulse);
LCD_ShowString(257,430,32,32,32,pulsenumber,1);
if(pulse==PULSE_DOUT) LCD_ShowString(257,471,100,32,32,"PASS",1);
else LCD_ShowString(257,471,100,32,32,"FAIL",1);
if((pulse%2)&&(((VALTAGE_MIN<((uint8_t)val_float))&&((uint8_t)val_float)<VALTAGE_MAX))&&(((CURRENT_MIN<(uint8_t)current_float)&&((uint8_t)current_float)<CURRENT_MAX)))//判断输出脉冲Dout=2,电流90ma<current<110ma,电压3v<valtage<6V
LCD_ShowBigString(156,566,230,148,148," !#$",BIGWORD_GREENCOLOR,1);// !"#$�?????注意这里是用字符代替显示内容，因为flash不够无需导入多余的字符显示，其真正的数据�?????"PASS"对应的数据标�?????
else
LCD_ShowBigString(156,566,230,148,148,"%&'(",BIGWORD_REDCOLOR,1);//注意这里是用字符代替显示内容，因为flash不够无需导入多余的字符显示，真正的数据为"FAILED"对应的数据标�?????
pulse=0;

while(current_float>10);

}

}
else
{
LCD_ShowString(257,430,32,32,32,"   ",1);
LCD_ShowBigString(156,566,400,148,148,"%&'(",BIGWORD_ClEARCOLOR,1);//注意这里是用字符代替显示内容，因为flash不够无需导入多余的字符显示，真正的数据为"FAILED"对应的数据标�?????
LCD_ShowBigString(155,562,400,148,148,"%&'(",BIGWORD_ClEARCOLOR,1);//注意这里是用字符代替显示内容，因为flash不够无需导入多余的字符显示，真正的数据为"FAILED"对应的数据标�?????
rgbset.R=0;
rgbset.G=0;
rgbset.B=0;
resultflag=0;
}


// vE2romTest();
    osDelay(2);
  }
  /* USER CODE END StartAT24C16Start */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */
void client(void)
{
		{
			int sock = -1;
			struct sockaddr_in client_addr;
			uint8_t send_buf[] = "This is a TCP client test \r\n";

			while(1)
			{
				sock = socket(AF_INET, SOCK_STREAM, 0);
				if(sock < 0)
				{
					osDelay(10);
					continue;
				}
				client_addr.sin_family = AF_INET;
				client_addr.sin_port = htons(PORT);
				client_addr.sin_addr.s_addr = inet_addr(IP_ADDR);
				memset(&(client_addr.sin_zero), 0, sizeof(client_addr.sin_zero));

				if(connect(sock, (struct sockaddr*)&client_addr, sizeof(struct sockaddr)) == -1)
				{
					printf("connect failed \r\n");
					closesocket(sock);
					osDelay(10);
					continue;
				}
				printf("connect to iperf server successful!\n");

				while(1)
				{
					if(write(sock, send_buf, sizeof(send_buf)) < 0)
						break;
					osDelay(10);
				}
				closesocket(sock);
			}
		}
}
/* USER CODE END Application */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
