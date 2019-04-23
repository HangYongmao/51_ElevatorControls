#include "main.h"

// 系统计时时钟
unsigned char clock=0;

// 代表电梯当前所在的楼层,初始在1楼
extern uchar currentFloor;

// 电梯当前的状态
extern enum FloorDirection floorDir;

// 存储每楼层的状态,代表是否需要开门
extern uchar floorStatus[9];

void InitTimer0()
{
    TMOD &= 0xf0;
    TH0 = (8192-4607)/32;
	TL0 = (8192-4607)%32;
	EA = 1;
	ET0 = 1;    // 定时器0 中断打开
	TR0 = 0;    // 定时器0 关闭
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
        TR0 = 0;    // 定时器0 关闭
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
