/*
*  基于单片机的电梯控制模块设计
*  CPU:STC89C52RC
*  晶振:11.0592MHZ
*  算法核心:
*    电梯如果停在四楼, 一楼和七楼如果同时有人按了,
*    这种情况下, 取决于前一次的状态,
*    如果处于向下的过程中, 则继续向下, 先到达一楼,
*    即 保持电梯之前的状态不变.
*  程序特色:
*    1.支持同时按下多个楼层
*    2.支持取消楼层
*/

#include "main.h"
#include "LCD1602.h"
#include "Key.h"
#include "L298N.h"

// 代表电梯当前所在的楼层,初始在1楼
uchar currentFloor=1;

// 存储每楼层的状态,代表是否需要开门
uchar floorStatus[9] = {0};

// 存储楼层对应的按键码,第i层的按键码为FloorData[i]
uchar code FloorData[] = {Floor_No,Floor_1,Floor_2,Floor_3,Floor_4,Floor_5,Floor_6,Floor_7,Floor_8};

// 电梯当前的状态
enum FloorDirection floorDir=Stop;

// 延时 z ms
void delay_ms(uint z)
{
	uint x, y;
	for (x = z; x>0; x--)
        for (y = 110; y>0; y--);
}

// 主函数
void main()
{
    int keyStatus=Floor_No;
    int i=0;
    // 初始化液晶
    init_LCD();
    while(1)
    {
        keyStatus = keyScan();
        
        // 判断当前是否有楼层被按下, 支持多个楼层同时按下
        for(i=1; i<=8; i++)
        {
            // 解析按下的楼层数据, 将对应楼层被按下的标志取反, 相当于 提供取消按键的功能
            if ((keyStatus|FloorData[i]) == FloorData[i])
                floorStatus[i] = !floorStatus[i];
        }
        // 在液晶的第一行显示
        write_com(0x80);
        
        // 显示当前所在的楼层
        write_date(currentFloor+'0');
        write_date(' ');
        
        for(i=1; i<=8; i++)
        {
            // 显示需要开门的楼层
            if (floorStatus[i])
                write_date(i+'0');
        }
        for(i=1; i<=8; i++)
        {
            // 当前所在的楼层需要开门
            if((floorStatus[i] == 1) && (i == currentFloor))
            {
                floorDir = Open;
                break;
            }
        }
        // 在液晶的第二行显示
        write_com(0x80+0x40);
        switch(floorDir)
        {
        case UP:    // 0-向上
            // 电梯上升
            L298N_UP();
            break;
        
        case Down:   // 1-向下
            // 电梯下降
            L298N_Down();
            break;
        
        case Stop:   // 2-停止
            // 电梯停止
            L298N_Stop();
            break;

        case Open:   // 3-开门
            LCD_ShowStr("Open");
            // 电梯停止
            L298N_Stop();
            break;
        
        case Close:  // 4-关门
            // 电梯停止
            L298N_Stop();
            break;
        }
    }
}
