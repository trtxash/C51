/*
04_LED矩阵
    功能
        逐行扫描，led显示出几个汉字或字母
    目的
        1 掌握led显示编程
        2 
*/

#include "reg51.h"   // 在reg52.h文件中已经定于过了RCLK,所以用reg51.h
#include <intrins.h> // 一般程序中需要使用到空指令_nop_();字符循环移位指令_crol_等时使用。

typedef unsigned int u16;
typedef unsigned char u8;

sbit SRCLK = P3 ^ 6; // 位移寄存器时钟输入
sbit RCLK = P3 ^ 5;  // 储存寄存器时钟输入
sbit SER = P3 ^ 4;   // 串行数据输入

u8 ledwei[] = {0x7f, 0xbf, 0xdf, 0xef, 0xf7, 0xfb, 0xfd, 0xfe};  // led位选
u8 ledduan[] = {0x00, 0x00, 0x3e, 0x41, 0x41, 0x41, 0x3e, 0x00}; // led段选

/*******************************************************************************
* 函 数 名      : Delay
* 函数功能      : 延时函数
* 输    入      : unsigned int
* 输    出      : 无
* 注            ：S = 0.00001T + 0.00002 = 1E-05x + 2E-05
*******************************************************************************/
void Delay(u16 i);

void Hc595SendByte(u8 dat);

/*******************************************************************************
* 函 数 名      : main
* 函数功能      : 主函数
* 输    入      : 
* 输    出      : 
*******************************************************************************/
void main()
{
    u8 i;
    while (1)
    {
        P0 = 0x7f;
        for (i = 0; i < 8; i++)
        {
            P0 = ledwei[i];            //位选
            Hc595SendByte(ledduan[i]); //发送段选数据
            Delay(5000);               //延时
            Hc595SendByte(0x00);       //消隐
        }
    }
}

void Delay(u16 i)
{
    while (i--)
        ;
}

void Hc595SendByte(u8 dat)
{
    u8 i;
    SRCLK = 0;
    RCLK = 0;

    for (i = 0; i < 8; i++) // 位移寄存器
    {
        SER = dat >> 7;
        dat <<= 1;

        SRCLK = 1;
        _nop_();
        _nop_();
        SRCLK = 0;
    }
    RCLK = 1; // 存储寄存器
    _nop_();
    _nop_();
    RCLK = 0;
}

// 2021年8月10号17点04分