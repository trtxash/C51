/*
03_动态数码管和矩阵按钮
    功能
        矩阵按钮各代表不同数字和功能，按下通过动态数码管显示出来
    目的
        1 掌握逐行扫描
        2 掌握矩阵按钮扫描方式
*/

#include "reg52.h"

////////////////////////////////////////////////////////////////////////////////
typedef unsigned int u16;
typedef unsigned char u8;

sbit LSA = P2 ^ 2;
sbit LSB = P2 ^ 3;
sbit LSC = P2 ^ 4;

////////////////////////////////////////////////////////////////////////////////
u8 code smgduan[17] = {0X00, 0X3F, 0X06, 0X5B, 0X4F, 0X66, 0X6D, 0X7D, 0X07, 0X7F, 0X6F, 0X77, 0X7C, 0X39, 0X5E, 0X79, 0X71}; //显示0~F的值

////////////////////////////////////////////////////////////////////////////////

/*******************************************************************************
* 函 数 名      : Delay
* 函数功能      : 延时函数
* 输    入      : unsigned int
* 输    出      : 
* 注            ：S = 0.00001T + 0.00002 = 1E-05x + 2E-05
*******************************************************************************/
void Delay(u16 i)
{
    while (i--)
        ;
}

/*******************************************************************************
* 函 数 名      : Display_Dealy
* 函数功能      : 显示和延时函数
* 输    入      : unsigned int,unsigned char[0~7]为第0~7位数码管的显示数字,unsigned char延时参数
* 输    出      : 
* 注            ：S = 0.00001T + 0.00002 = 1E-05x + 2E-05,t = 85为144HZ左右
*******************************************************************************/
void Display_Dealy(u8 smgxianshi[], u8 t)
{
    u8 s = 16;

    while (s--) // s控制函数运行时长，达到按键消抖的作用
    {
        u8 i;

        for (i = 0; i < 8; i++)
        {
            P0 = 0X00; //消隐
            switch (i) //位选，选择点亮的数码管，
            {
            case (0):
                LSA = 1;
                LSB = 1;
                LSC = 1;
                break; //显示第0位
            case (1):
                LSA = 0;
                LSB = 1;
                LSC = 1;
                break; //显示第1位
            case (2):
                LSA = 1;
                LSB = 0;
                LSC = 1;
                break; //显示第2位
            case (3):
                LSA = 0;
                LSB = 0;
                LSC = 1;
                break; //显示第3位
            case (4):
                LSA = 1;
                LSB = 1;
                LSC = 0;
                break; //显示第4位
            case (5):
                LSA = 0;
                LSB = 1;
                LSC = 0;
                break; //显示第5位
            case (6):
                LSA = 1;
                LSB = 0;
                LSC = 0;
                break; //显示第6位
            case (7):
                LSA = 0;
                LSB = 0;
                LSC = 0;
                break; //显示第7位
            }
            P0 = smgxianshi[i];
            Delay(t); // 延时控制频率HZ
        }
    }
}

/*******************************************************************************
* 函 数 名      : KeyDown
* 函数功能      : 检测有按键按下并读取键值
* 输    入      : 
* 输    出      : unsigned char,1~16
*******************************************************************************/
u8 KeyDown(void)
{
    u8 KeyValue; //用来存放读取到的键值
    P1 = 0X0F;

    if (P1 != 0X0F) //读取按键是否按下
    {
        switch (P1) //测试列
        {
        case (0X07):
            KeyValue = 1;
            break;
        case (0X0B):
            KeyValue = 2;
            break;
        case (0X0D):
            KeyValue = 3;
            break;
        case (0X0E):
            KeyValue = 4;
            break;
        }
        P1 = 0XF0; //测试行
        switch (P1)
        {
        case (0X70):
            KeyValue = KeyValue;
            break;
        case (0Xb0):
            KeyValue = KeyValue + 4;
            break;
        case (0Xd0):
            KeyValue = KeyValue + 8;
            break;
        case (0Xe0):
            KeyValue = KeyValue + 12;
            break;
        }
        return KeyValue;
    }
    return 0;
}

/*******************************************************************************
* 函 数 名      : main
* 函数功能      : 主函数
* 输    入      : 
* 输    出      : unsigned char
*******************************************************************************/
void main(void)
{
    u8 smgxianshi[8]; // 让8个8段数码管显示0~7中的数字

    while (1)
    {
        if (KeyDown()) // 按下键第八位接受最新数字
        {
            if (smgxianshi[7] == 0X00)
            {
                smgxianshi[7] = smgduan[KeyDown()];
            }
            else
            {
                u8 i;

                for (i = 0; i < 7; i++)
                {
                    smgxianshi[i] = smgxianshi[i + 1];
                }
                smgxianshi[7] = smgduan[KeyDown()];
            }
        }
        Display_Dealy(smgxianshi, 85); // 延时显示函数
    }
}

// 2021年8月14号20点11分