/*
00_蜂鸣器和独立按键
    功能
        按下不同独立按键蜂鸣器发出不同响声
    目的
        1 练习独立按键和蜂鸣器

*/

#include "reg52.h"

typedef unsigned int u16;
typedef unsigned char u8;

sbit beep = P1 ^ 5;

/*******************************************************************************
* 函 数 名       : delay
* 函数功能		 : 延时函数
* 输    入       : unsigned int
* 输    出    	 : 无
* 注			 ：i=1时，大约延时10us
*******************************************************************************/
void delay(u16 i);

/*******************************************************************************
* 函 数 名       : main
* 函数功能		 : 主函数
* 输    入       : 
* 输    出    	 : 
*******************************************************************************/
void main()
{
    while (1)
    {
        beep=~beep;
        delay(100);
    }
}

void delay(u16 i)
{
    while (i--)
        ;
}

// 2021年8月10号17点04分