#ifndef __MAIN_H__
#define __MAIN_H__

#include <reg52.h>
#include <intrins.h>

#define uchar unsigned char
#define uint  unsigned int

// 楼层
enum FloorStatus{
    Floor_No=0xFF,  // 没有按下楼层
    Floor_1 =0xFE,  // 1楼
    Floor_2 =0xFD,  // 2楼
    Floor_3 =0xFB,  // 3楼
    Floor_4 =0xF7,  // 4楼
    Floor_5 =0xEF,  // 5楼
    Floor_6 =0xDF,  // 6楼
    Floor_7 =0xBF,  // 7楼
    Floor_8 =0x7F,  // 8楼
};

// 电梯当前的状态
enum FloorDirection{
    UP,     // 0-向上
    Down,   // 1-向下
    Stop,   // 2-停止
    Open,   // 3-开门
    Close,  // 4-关门
};

// LCD1602
sbit LCD_RS = P2 ^ 0;	// 液晶数据命令选择端
sbit LCD_RW = P2 ^ 1;   // 读/写选择端(H/L)
sbit LCD_EN = P2 ^ 2;   // 液晶使能端
sfr LCD_Port= 0x80;     // P0

// L298N 直流电机
sbit L298N_IN1 = P2 ^ 7;
sbit L298N_IN2 = P2 ^ 5;

// 蜂鸣器
sbit Beep = P2 ^ 6;

// 按键
sfr EleButton = 0xB0;

// 延时 z ms
void delay_ms(uint z);

#endif
