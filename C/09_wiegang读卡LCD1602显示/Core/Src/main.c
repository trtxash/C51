/*
09_wiegang读卡LCD1602显示
    功能
        通过读卡器读卡，LCD1602显示信息
    目的
        练习LCD显示，读卡器的使用
*/
#include <main.h>

////////////////////////////////////////////////////////////////////////////////
typedef unsigned int u16;
typedef unsigned char u8;

wiegand_dev wiegand_dev_t; // 定义一个结构体，用于存储韦根卡的数据

/******************************************************************************
 *函数名称：main( )
 *函数功能：主函数
 *入口函数：无
 *出口函数：无
 ****************************************************************************/
void main() using 0
{
    initial();
    LcdInit();
    wiegand_dev_t.global_var = 0;

    while (1)
    {
        if (wiegand_dev_t.global_var == 34)
        {
            wiegand_dev_t.global_var = 0;
            LcdPrintf(wiegand_dev_t.wiegand);
        }
    }
}

/******************************************************************************
 *函数名称：Wiegand_Data0( )
 *函数功能：韦根卡数据0中断处理
 *入口函数：无
 *出口函数：无
 ******************************************************************************/
void Wiegand_Data0() interrupt 0 using 1 //中断0处理函数,使用第一组寄存器，main函数使用0组寄存器，写好寄存器组可以省去寄存器入栈，提高速度
{
    EX0 = 0;
    wiegand_dev_t.wiegand[wiegand_dev_t.global_var] = '0';
    wiegand_dev_t.global_var += 1;
    udelay(100);
    EX0 = 1;
}

/******************************************************************************
 *函数名称：Wiegand_Data1( )
 *函数功能：韦根卡数据1中断处理
 *入口函数：无
 *出口函数：无
 ******************************************************************************/
void Wiegand_Data1() interrupt 2 using 2 //中断1处理函数,使用第二组寄存器
{
    EX1 = 0;
    wiegand_dev_t.wiegand[wiegand_dev_t.global_var] = '1';
    wiegand_dev_t.global_var += 1;
    udelay(100);
    EX1 = 1;
}

// 2022年6月26号11点35分