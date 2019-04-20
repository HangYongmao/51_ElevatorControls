#ifndef __MAIN_H__
#define __MAIN_H__

#include <reg52.h>
#include <intrins.h>

#define uchar unsigned char
#define uint  unsigned int

// ¥��
enum FloorStatus{
    Floor_No=0xFF,  // û�а���¥��
    Floor_1 =0xFE,  // 1¥
    Floor_2 =0xFD,  // 2¥
    Floor_3 =0xFB,  // 3¥
    Floor_4 =0xF7,  // 4¥
    Floor_5 =0xEF,  // 5¥
    Floor_6 =0xDF,  // 6¥
    Floor_7 =0xBF,  // 7¥
    Floor_8 =0x7F,  // 8¥
};

// ���ݵ�ǰ��״̬
enum FloorDirection{
    UP,     // 0-����
    Down,   // 1-����
    Stop,   // 2-ֹͣ
    Open,   // 3-����
    Close,  // 4-����
};

// LCD1602
sbit LCD_RS = P2 ^ 0;	// Һ����������ѡ���
sbit LCD_RW = P2 ^ 1;   // ��/дѡ���(H/L)
sbit LCD_EN = P2 ^ 2;   // Һ��ʹ�ܶ�
sfr LCD_Port= 0x80;     // P0

// L298N ֱ�����
sbit L298N_IN1 = P2 ^ 7;
sbit L298N_IN2 = P2 ^ 5;

// ������
sbit Beep = P2 ^ 6;

// ����
sfr EleButton = 0xB0;

// ��ʱ z ms
void delay_ms(uint z);

#endif
