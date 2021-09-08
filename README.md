# DS_SourceCode

#### 介绍
{**本代码适用于达实智控科技，任何问题请与达实智控研发部联系}

#### 软件架构
软件架构说明
FreeRtos

#### 安装教程

1.  本代码使用STM32cubeIDE搭建
2.  本代码仅使用于达实智控测试开板
3.  代码使用时必须参照达实智控测试板的线路

#### 使用说明

1.  导入stm32f429工程
2.  编译
3.  UART5定义为debugging以作为printf调试输出

#### 更新和维护

1.  增加RGB_fixtrue定义，在非调试rgb灯时，宏定义为0，防止while(current>10);无限等待；
2.  增加SPI_flash读取像素，将MCU flash 释放512KB出来用于 IAP https升级程序。。。。



#### 已知bug:

1.  CAN口连接正常后，五分钟无数据系统死机；
2.  无实物RGB灯板时，防止while(current>10);无限等待；
3.  每次初始化cubmx HAL配置后都要重定义 SPI flash DMA callback使能，因为默认cubmx未始能
4. TFT_LCD局部刷屏时，每次刷屏都必须按从上到下顺序局部依次刷屏，不可从下到上，再到下，会出现雪花点

