#include "main.h"
#include <string.h>

// д����
void write_com(uchar com)
{
	LCD_RS = 0;	//����ѡ��
	LCD_RW = 0;
	LCD_Port = com;
	delay_ms(5);
	LCD_EN = 1;	//ʹ��E��
	delay_ms(5);
	LCD_EN = 0;	//ʹ��E��
	delay_ms(5);
}

// д����
void write_date(uchar date)
{
	LCD_RS = 1;	//����ѡ��
	LCD_RW = 0;
	LCD_Port = date;
	delay_ms(5);
	LCD_EN = 1;	//ʹ��E��
	delay_ms(5);
	LCD_EN = 0;	//ʹ��E��
}

// LCD��ʼ��
void init_LCD()
{
	LCD_EN = 0;
	write_com(0x38);	// ����16x2��ʾ��5x7����8λ���ݽӿ�
	write_com(0x0c);	// ���ÿ���ʾ������ʾ���
	write_com(0x06);	// дһ���ַ��󣬵�ַָ���1
	write_com(0x01);	// ��ʾ��0������ָ����0
}

// ��Һ������ʾ�ַ���
void LCD_ShowStr(char * str)
{
    int length = strlen(str);
    while(length--)
    {
        write_date(*str++);
    }
}