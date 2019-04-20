/*
*  基于单片机的电梯控制模块设计
*  CPU:STC89C52RC
*  晶振:11.0592MHZ
*/

#include "main.h"
#include "LCD1602.h"

// 延时 z ms
void delay_ms(uint z)
{
	uint x, y;
	for (x = z; x>0; x--)
        for (y = 110; y>0; y--);
}

// 主函数
void main()
{
    // 初始化液晶
    init_LCD();

    // LCD显示 第一行
    write_com(0x80+0x01);
    LCD_ShowStr("Welcome To Use");
    LCD_ShowInt(123);
    while(1)
    {
    }
}
