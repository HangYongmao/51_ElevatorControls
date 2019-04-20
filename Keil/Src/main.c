/*
*  ���ڵ�Ƭ���ĵ��ݿ���ģ�����
*  CPU:STC89C52RC
*  ����:11.0592MHZ
*/

#include "main.h"
#include "LCD1602.h"

// ��ʱ z ms
void delay_ms(uint z)
{
	uint x, y;
	for (x = z; x>0; x--)
        for (y = 110; y>0; y--);
}

// ������
void main()
{
    // ��ʼ��Һ��
    init_LCD();

    // LCD��ʾ ��һ��
    write_com(0x80+0x01);
    LCD_ShowStr("Welcome To Use");
    LCD_ShowInt(123);
    while(1)
    {
    }
}
