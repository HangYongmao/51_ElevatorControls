#ifndef __MAIN_H__
#define __MAIN_H__

#include <reg52.h>

#define uchar unsigned char
#define uint  unsigned int

// LCD1602
sbit LCD_RS = P2 ^ 0;	// Һ����������ѡ���
sbit LCD_RW = P2 ^ 1;   // ��/дѡ���(H/L)
sbit LCD_EN = P2 ^ 2;   // Һ��ʹ�ܶ�
sfr LCD_Port= 0x80;

// ��ʱ z ms
void delay_ms(uint z);

#endif
