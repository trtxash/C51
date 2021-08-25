/*
02_蜂鸣器和独立按键
    功能
        按下任意一个独立按键蜂鸣器发出哆来咪发唆拉稀，再按下停止，不发声时led灯亮
    目的
        1 练习独立按键和蜂鸣器
        2 测试一下延时函数的延时时间参数

*/

#include "reg52.h"

////////////////////////////////////////////////////////////////////////////////
typedef unsigned int u16;
typedef unsigned char u8;

#define led P2

sbit beep = P1 ^ 5;
sbit key0 = P3 ^ 1;
sbit key1 = P3 ^ 0;
sbit key2 = P3 ^ 2;
sbit key3 = P3 ^ 3;

////////////////////////////////////////////////////////////////////////////////
void Delay(u16 i);

////////////////////////////////////////////////////////////////////////////////

/*******************************************************************************
* 函 数 名       : main
* 函数功能		 : 主函数
* 输    入       : 
* 输    出    	 : 
*******************************************************************************/
void main(void)
{
    u16 i;
    led = 0X00; //开led

    while (1)
    {
        if ((key0 && key1 && key2 && key3) == 0) // 第一次按下独立按键
        {
            led = 0XFF;   // 关led
            Delay(19998); //200ms按键消抖
            while (1)
            {
                for (i = 3998; key0 && key1 && key2 && key3 && i; i--) //duo
                {
                    beep = ~beep;
                    Delay(46);
                }
                if ((key0 && key1 && key2 && key3) == 0) // 第二次按下独立按键中止循环
                    break;

                for (i = 3998; key0 && key1 && key2 && key3 && i; i--) //lai
                {
                    beep = ~beep;
                    Delay(41);
                }
                if ((key0 && key1 && key2 && key3) == 0)
                    break;
                for (i = 3998; key0 && key1 && key2 && key3 && i; i--) //mi
                {
                    beep = ~beep;
                    Delay(36);
                }
                if ((key0 && key1 && key2 && key3) == 0)
                    break;
                for (i = 3998; key0 && key1 && key2 && key3 && i; i--) //fa
                {
                    beep = ~beep;
                    Delay(34);
                }
                if ((key0 && key1 && key2 && key3) == 0)
                    break;
                for (i = 3998; key0 && key1 && key2 && key3 && i; i--) //so
                {
                    beep = ~beep;
                    Delay(30);
                }
                if ((key0 && key1 && key2 && key3) == 0)
                    break;
                for (i = 3998; key0 && key1 && key2 && key3 && i; i--) //la
                {
                    beep = ~beep;
                    Delay(26);
                }
                if ((key0 && key1 && key2 && key3) == 0)
                    break;
                for (i = 3998; key0 && key1 && key2 && key3 && i; i--) //xi
                {
                    beep = ~beep;
                    Delay(23);
                }
                if ((key0 && key1 && key2 && key3) == 0)
                    break;
            }
            led = 0X00;
            Delay(19998);
        }
    }
}

/*******************************************************************************
* 函 数 名       : Delay
* 函数功能		 : 延时函数
* 输    入       : unsigned int
* 输    出    	 : 
* 注			 ：S = 0.00001T + 0.00002 = 1E-05x + 2E-05
*******************************************************************************/
void Delay(u16 i)
{
    while (i--)
    {
    }
}

// 2021年8月11号21点58分