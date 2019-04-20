#include "main.h"
#include <string.h>

// 写命令
void write_com(uchar com)
{
	LCD_RS = 0;	//命令选择
	LCD_RW = 0;
	LCD_Port = com;
	delay_ms(5);
	LCD_EN = 1;	//使能E开
	delay_ms(5);
	LCD_EN = 0;	//使能E关
	delay_ms(5);
}

// 写数据
void write_date(uchar date)
{
	LCD_RS = 1;	//数据选择
	LCD_RW = 0;
	LCD_Port = date;
	delay_ms(5);
	LCD_EN = 1;	//使能E开
	delay_ms(5);
	LCD_EN = 0;	//使能E关
}

// LCD初始化
void init_LCD()
{
	LCD_EN = 0;
	write_com(0x38);	// 设置16x2显示，5x7点阵，8位数据接口
	write_com(0x0c);	// 设置开显示，不显示光标
	write_com(0x06);	// 写一个字符后，地址指针加1
	write_com(0x01);	// 显示清0，数据指针清0
}

// 在液晶上显示数字
void LCD_ShowInt(uint num)
{
    int n=num, length=0;
    if (num == 0)
    {
        write_date('0');
        return;
    }
    
    while(n)// 当n不等于0时执行循环
    {
        n=n/10;     // n的长度减去1
        length++;   // length+1
    }
    switch(length)
    {
        case 5:
            write_date(num/10000+'0');
        case 4:
            write_date(num%10000/1000+'0');
        case 3:
            write_date(num%1000/100+'0');
        case 2:
            write_date(num%100/10+'0');
        case 1:
            write_date(num%10+'0');
    }
}

// 在液晶上显示字符串
void LCD_ShowStr(char * str)
{
    int length = strlen(str);
    while(length--)
    {
        write_date(*str++);
    }
}