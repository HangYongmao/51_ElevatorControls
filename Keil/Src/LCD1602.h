#ifndef __LCD1602_H__
#define __LCD1602_H__

#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// д����
void write_com(uchar com);

// д����
void write_date(uchar date);

// LCD��ʼ��
void init_LCD();

// ��Һ������ʾ����
void LCD_ShowInt(uint num);

// ��Һ������ʾ�ַ���
void LCD_ShowStr(char * str);

#endif