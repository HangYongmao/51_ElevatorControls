#include "main.h"

// ϵͳ��ʱʱ��
unsigned char clock=0;

// ������ݵ�ǰ���ڵ�¥��,��ʼ��1¥
extern uchar currentFloor;

// ���ݵ�ǰ��״̬
extern enum FloorDirection floorDir;

// �洢ÿ¥���״̬,�����Ƿ���Ҫ����
extern uchar floorStatus[9];

void InitTimer0()
{
    TMOD &= 0xf0;
    TH0 = (8192-4607)/32;
	TL0 = (8192-4607)%32;
	EA = 1;
	ET0 = 1;    // ��ʱ��0 �жϴ�
	TR0 = 0;    // ��ʱ��0 �ر�
}

void T0_time() interrupt 1
{
    static unsigned char num;
    int i=0;
	TH0 = (8192-4607)/32;
	TL0 = (8192-4607)%32;
	num++;
    if(num%200 == 0)
    {
        num = 0;
        clock ++;
    }
    if (clock == 5)
    {
        TR0 = 0;    // ��ʱ��0 �ر�
        clock = 0;
        if (floorDir == Down)
        {
            if (currentFloor > 1)
                currentFloor--;
        }
        else if (floorDir == UP)
        {
            if (currentFloor < 8)
                currentFloor++;
        }
        else if (floorDir == Open)
        {
            floorDir = Close;
        }
        else if (floorDir == Close)
        {
            floorDir = Stop;
        }
    }
}
