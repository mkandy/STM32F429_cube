#include "sys.h"
#include "lcd.h" 
//ALIENTEK 阿波罗STM32F429开发板 实验30
//触摸屏 实验
//技术支持：www.openedv.com
//广州市星翼电子科技有限公司

//清空屏幕并在右上角显示"RST"
void Load_Drow_Dialog(void)
{
	LCD_Clear(WHITE);//清屏
 	POINT_COLOR=BLUE;//设置字体为蓝色
	LCD_ShowString(lcddev.width-24,0,200,16,16,"RST",0);//显示清屏区域
  	POINT_COLOR=RED;//设置画笔蓝色
}
////////////////////////////////////////////////////////////////////////////////
//电容触摸屏专有部分
//画水平线
//x0,y0:坐标
//len:线长度
//color:颜色
void gui_draw_hline(u16 x0,u16 y0,u16 len,u16 color)
{
	if(len==0)return;
	if((x0+len-1)>=lcddev.width)x0=lcddev.width-len-1;	//限制坐标范围
	if(y0>=lcddev.height)y0=lcddev.height-1;			//限制坐标范围
	LCD_Fill(x0,y0,x0+len-1,y0,color);	
}
//画实心圆
//x0,y0:坐标
//r:半径
//color:颜色
void gui_fill_circle(u16 x0,u16 y0,u16 r,u16 color)
{											  
	u32 i;
	u32 imax = ((u32)r*707)/1000+1;
	u32 sqmax = (u32)r*(u32)r+(u32)r/2;
	u32 x=r;
	gui_draw_hline(x0-r,y0,2*r,color);
	for (i=1;i<=imax;i++) 
	{
		if ((i*i+x*x)>sqmax)// draw lines from outside  
		{
 			if (x>imax) 
			{
				gui_draw_hline (x0-i+1,y0+x,2*(i-1),color);
				gui_draw_hline (x0-i+1,y0-x,2*(i-1),color);
			}
			x--;
		}
		// draw lines from inside (center)  
		gui_draw_hline(x0-x,y0+i,2*x,color);
		gui_draw_hline(x0-x,y0-i,2*x,color);
	}
}  
//两个数之差的绝对值
//x1,x2：需取差值的两个数
//返回值：|x1-x2|
u16 my_abs(u16 x1,u16 x2)
{			 
	if(x1>x2)return x1-x2;
	else return x2-x1;
}  
//画一条粗线
//(x1,y1),(x2,y2):线条的起始坐标
//size：线条的粗细程度
//color：线条的颜色
void lcd_draw_bline(u16 x1, u16 y1, u16 x2, u16 y2,u8 size,u16 color)
{
	u16 t; 
	int xerr=0,yerr=0,delta_x,delta_y,distance; 
	int incx,incy,uRow,uCol; 
	if(x1<size|| x2<size||y1<size|| y2<size)return; 
	delta_x=x2-x1; //计算坐标增量
	delta_y=y2-y1; 
	uRow=x1; 
	uCol=y1; 
	if(delta_x>0)incx=1; //设置单步方向
	else if(delta_x==0)incx=0;//垂直线
	else {incx=-1;delta_x=-delta_x;} 
	if(delta_y>0)incy=1; 
	else if(delta_y==0)incy=0;//水平线
	else{incy=-1;delta_y=-delta_y;} 
	if( delta_x>delta_y)distance=delta_x; //选取基本增量坐标轴
	else distance=delta_y; 
	for(t=0;t<=distance+1;t++ )//画线输出
	{  
		gui_fill_circle(uRow,uCol,size,color);//画点
		xerr+=delta_x ; 
		yerr+=delta_y ; 
		if(xerr>distance) 
		{ 
			xerr-=distance; 
			uRow+=incx; 
		} 
		if(yerr>distance) 
		{ 
			yerr-=distance; 
			uCol+=incy; 
		} 
	}  
}   

void lcdtest(void)
{      

  	POINT_COLOR=RED;
 	Load_Drow_Dialog();	 	
	LCD_ShowString(30,50,200,16,16,"DS STM32F4/F7",0);
	LCD_ShowString(30,70,200,16,16,"LCD TEST",0);
	LCD_ShowString(30,90,200,16,16,"ATOM@ALIENTEK",0);
	LCD_ShowString(30,110,200,16,16,"2021/8/5",0);
	POINT_COLOR=BLACK;    //LCD画笔为黑色

	//LCD_Color_Fill(1,1,LOGO_W,LOGO_H,(uint16_t*)sky_animation_mask); //指定区域填充色块（color为色块数组）
}

















