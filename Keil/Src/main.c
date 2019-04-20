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

// ������ݵ�ǰ���ڵ�¥��,��ʼ��1¥
uchar currentFloor=1;

// �洢ÿ¥���״̬,�����Ƿ���Ҫ����
uchar floorStatus[9] = {0};

// �洢¥���Ӧ�İ�����,��i��İ�����ΪFloorData[i]
uchar code FloorData[] = {Floor_No,Floor_1,Floor_2,Floor_3,Floor_4,Floor_5,Floor_6,Floor_7,Floor_8};

// ���ݵ�ǰ��״̬
enum FloorDirection floorDir=Stop;

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
    int keyStatus=Floor_No;
    int i=0;
    // ��ʼ��Һ��
    init_LCD();
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
        write_date(currentFloor+'0');
        write_date(' ');
        
        for(i=1; i<=8; i++)
        {
            // ��ʾ��Ҫ���ŵ�¥��
            if (floorStatus[i])
                write_date(i+'0');
        }
        for(i=1; i<=8; i++)
        {
            // ��ǰ���ڵ�¥����Ҫ����
            if((floorStatus[i] == 1) && (i == currentFloor))
            {
                floorDir = Open;
                break;
            }
        }
        // ��Һ���ĵڶ�����ʾ
        write_com(0x80+0x40);
        switch(floorDir)
        {
        case UP:    // 0-����
            // ��������
            L298N_UP();
            break;
        
        case Down:   // 1-����
            // �����½�
            L298N_Down();
            break;
        
        case Stop:   // 2-ֹͣ
            // ����ֹͣ
            L298N_Stop();
            break;

        case Open:   // 3-����
            LCD_ShowStr("Open");
            // ����ֹͣ
            L298N_Stop();
            break;
        
        case Close:  // 4-����
            // ����ֹͣ
            L298N_Stop();
            break;
        }
    }
}
