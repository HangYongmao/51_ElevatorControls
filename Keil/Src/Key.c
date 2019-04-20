#include "Key.h"

// 按键扫描
uchar keyScan()
{
    uchar status=Floor_No;
    if (EleButton != Floor_No)
    {
        delay_ms(10);
        if (EleButton != Floor_No)
        {
            status = EleButton;
            while(EleButton != Floor_No);   // 等待所有按键释放
        }
    }
    return status;
}