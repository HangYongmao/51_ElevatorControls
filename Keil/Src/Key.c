#include "Key.h"

// ����ɨ��
uchar keyScan()
{
    uchar status=Floor_No;
    if (EleButton != Floor_No)
    {
        delay_ms(10);
        if (EleButton != Floor_No)
        {
            status = EleButton;
            while(EleButton != Floor_No);   // �ȴ����а����ͷ�
        }
    }
    return status;
}