#ifndef __LCD1602_H__
#define __LCD1602_H__

#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 写命令
void write_com(uchar com);

// 写数据
void write_date(uchar date);

// LCD初始化
void init_LCD();

// 在液晶上显示数字
void LCD_ShowInt(uint num);

// 在液晶上显示字符串
void LCD_ShowStr(char * str);

#endif