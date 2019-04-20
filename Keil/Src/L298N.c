#include "L298N.h"

// 电梯上升
void L298N_UP()
{
    L298N_IN1 = 1;
    L298N_IN2 = 0;
}

// 电梯下降
void L298N_Down()
{
    L298N_IN1 = 0;
    L298N_IN2 = 1;
}

// 电梯停止
void L298N_Stop()
{
    L298N_IN1 = 0;
    L298N_IN2 = 0;
}