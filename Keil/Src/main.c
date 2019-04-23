/*
*  ���ڵ�Ƭ���ĵ��ݿ���ģ�����
*  CPU:STC89C52RC
*  ����:11.0592MHZ
*  �㷨����:
*    �������ͣ����¥, һ¥����¥���ͬʱ���˰���,
*    ���������, ȡ����ǰһ�ε�״̬,
*    ����������µĹ�����, ���������, �ȵ���һ¥,
*    �� ���ֵ���֮ǰ��״̬����.
*  ������ɫ:
*    1.֧��ͬʱ���¶��¥��
*    2.֧��ȡ��¥��
*/

#include "main.h"
#include "LCD1602.h"
#include "Key.h"
#include "L298N.h"
#include "Timer.h"

// ������ݵ�ǰ���ڵ�¥��,��ʼ��1¥
uchar currentFloor=1;

// �洢ÿ¥���״̬,�����Ƿ���Ҫ����
uchar floorStatus[9] = {0};

// �洢¥���Ӧ�İ�����,��i��İ�����ΪFloorData[i]
uchar code FloorData[] = {Floor_No,Floor_1,Floor_2,Floor_3,Floor_4,Floor_5,Floor_6,Floor_7,Floor_8};

// ���ݵ�ǰ��״̬
enum FloorDirection floorDir=Stop;

// ����֮ǰ��״̬
enum FloorDirection lastDir=UP;

// ϵͳ��ʱʱ��
extern unsigned char clock;

// ��ʱ z ms
void delay_ms(uint z)
{
	uint x, y;
	for (x = z; x>0; x--)
        for (y = 114; y>0; y--);
}

// ������
void main()
{
    int keyStatus=Floor_No;
    int i=0;
    
    // ��ʼ��Һ��
    init_LCD();
    
    // ��ʼ����ʱ
    InitTimer0();
    while(1)
    {
        keyStatus = keyScan();
        
        // �жϵ�ǰ�Ƿ���¥�㱻����, ֧�ֶ��¥��ͬʱ����
        for(i=1; i<=8; i++)
        {
            // �������µ�¥������, ����Ӧ¥�㱻���µı�־ȡ��, �൱�� �ṩȡ�������Ĺ���
            if ((keyStatus|FloorData[i]) == FloorData[i])
                floorStatus[i] = !floorStatus[i];
        }
        // ��Һ���ĵ�һ����ʾ
        write_com(0x80);
        
        // ��ʾ��ǰ���ڵ�¥��
        LCD_ShowStr("Floor:");
        write_date(currentFloor+'0');
        write_date(' ');
        
        for(i=1; i<=8; i++)
        {
            // ��ʾ��Ҫ���ŵ�¥��
            if (floorStatus[i])
                write_date(i+'0');
        }
        LCD_ShowStr("              ");
        
        // ���ǰһ�δ�������״̬ �жϵ�ǰ¥�㵽��¥֮���Ƿ���¥�㰴��
        if ((lastDir == UP || floorDir == Stop) && (lastDir != Down))
        {
            for(i=currentFloor; i<=8; i++)
            {
                // ��¥�㱻����
                if(floorStatus[i] == 1)
                {
                    // ��ǰ���ڵ�¥����Ҫ����
                    if (i == currentFloor)
                    {
                        if (clock == 0)
                        {
                            floorDir = Open;
                            break;
                        }
                    }
                    else
                    {
                        floorDir = UP;
                        lastDir  = UP;
                        break;
                    }
                }
            }
            // ���û�и�¥�㱻����
            if (i >= 9)
                lastDir = Down;
        }
        // ���ǰһ�δ����½�״̬ �жϵ�ǰ¥�㵽��¥֮���Ƿ���¥�㰴��
        if ((lastDir == Down || floorDir == Stop) && (lastDir != UP))
        {
            for(i=currentFloor; i>=1; i--)
            {
                // ��¥�㱻����
                if(floorStatus[i] == 1)
                {
                    // ��ǰ���ڵ�¥����Ҫ����
                    if (i == currentFloor)
                    {
                        if (clock == 0)
                        {
                            floorDir = Open;
                            break;
                        }
                    }
                    else
                    {
                        floorDir = Down;
                        lastDir  = Down;
                        break;
                    }
                }
            }
            // ���û�и�¥�㱻����
            if (i <= 0)
                lastDir = UP;
        }
        // ��Һ���ĵڶ�����ʾ
        write_com(0x80+0x40);
        switch(floorDir)
        {
        case UP:    // 0-����
            TR0 = 1;    // ��ʱ��0 ��
            LCD_ShowStr("Up   ");

            // ��������
            L298N_UP();
            break;
        
        case Down:   // 1-����
            TR0 = 1;    // ��ʱ��0 ��
            LCD_ShowStr("Down ");

            // �����½�
            L298N_Down();
            break;
        
        case Stop:   // 2-ֹͣ
            TR0 = 0;    // ��ʱ��0 ��
            LCD_ShowStr("Stop ");

            // ����ֹͣ
            L298N_Stop();
            break;

        case Open:   // 3-����
            TR0 = 1;    // ��ʱ��0 ��
            LCD_ShowStr("Open ");

            // ����ֹͣ
            L298N_Stop();
            if (clock == 0)
            {
                // ��������
                Beep = 0;
                delay_ms(300);
                Beep = 1;
            }

            // ���ź�,����Ӧ�ı�־��0,��ʾ������Ҫ����
            floorStatus[currentFloor] = 0;
            break;
        
        case Close:  // 4-����
            TR0 = 1;    // ��ʱ��0 ��
            LCD_ShowStr("Close");
            // ����ֹͣ
            L298N_Stop();
            break;
        }
    }
}
