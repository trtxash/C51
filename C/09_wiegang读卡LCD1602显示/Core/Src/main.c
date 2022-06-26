/*
09_wiegang读卡LCD1602显示
    功能
        通过读卡器读卡，LCD1602显示信息
    目的
        练习LCD显示，读卡器的使用
*/
#include <main.h>
#include "wiegand.h"

////////////////////////////////////////////////////////////////////////////////
typedef unsigned int u16;
typedef unsigned char u8;

u8 DisplayData[27] = ""; // 记录32位字符串

/******************************************************************************
 *函数名称：main( )
 *函数功能：主函数
 *入口函数：无
 *出口函数：无
 ****************************************************************************/
void main()
{
    initial();
    LcdInit();

    while (1)
    {
        u8 i;
 
        for (i = 0; i < 26; i++)
        {
            DisplayData[i] = rf_card->wiegand[i];
        }
        LcdPrintf(DisplayData);
        rf_card->global_var = 0;
    }
}

// 2022年6月26号11点35分