/*
07_数码管秒表和定时器中断
    功能
        利用定时器进行精准的秒表计时,利用动态数码管进行144hz刷新显示时钟
    目的
        1 复习计时器
        2 复习中断
*/

#include "reg52.h"

////////////////////////////////////////////////////////////////////////////////
typedef unsigned int u16;
typedef unsigned char u8;

sbit LSA = P2 ^ 2;
sbit LSB = P2 ^ 3;
sbit LSC = P2 ^ 4;

////////////////////////////////////////////////////////////////////////////////
u8 code smgduan[10] = {0X3F, 0X06, 0X5B, 0X4F, 0X66, 0X6D, 0X7D, 0X07, 0X7F, 0X6F}; //显示0~9的值
u8 smg[8] = {0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00};                       // 记录八段数码管的显示数据
u16 sss = 0, ssec = 0, sec = 0, min = 0, h = 0;                                     //次数，毫秒，秒，分 ,小时

////////////////////////////////////////////////////////////////////////////////
void Timer0Init(u8 x);              // 定时器0初始化函数
void Delay(u16 i);                  // 延时函数
void DataProcess(void);             // 数据处理函数
void DisplayDelay(u8 smgxianshi[]); // 显示和延时函数

////////////////////////////////////////////////////////////////////////////////

/*******************************************************************************
* 函 数 名      : main
* 函数功能      : 主函数
* 输    入      : 
* 输    出      : 
*******************************************************************************/
void main(void)
{
    Timer0Init(1); // 初始化计时器0

    while (1)
    {
        DataProcess(); // 用到了定时器0
        DisplayDelay(smg);
    }
}

/*******************************************************************************
* 函 数 名      : Timer0Init
* 函数功能      : 定时器初始化函数
* 输    入      : unsigned char
* 输    出      : 
*******************************************************************************/
void Timer0Init(u8 x)
{
    TMOD |= 0X02; // 设置工作方式为2，8位自动重装定时器,定时器读取内部时钟，计时器读取管脚脉冲
    TL0 = 0X00;   // 定时器0低八位赋初值
    TH0 = 0X00;   // 定时器0高八位赋初值
    ET0 = 1;      // 定时器0中断打开
    EA = 1;       // 总中断打开
    TR0 = x;      // 控制定时器，1为打开
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

/*******************************************************************************
* 函 数 名      : DataProcess
* 函数功能      : 数据处理函数
* 输    入      : 
* 输    出      : 
*******************************************************************************/
void DataProcess(void)
{
    smg[7] = smgduan[(h / 10) % 10];
    smg[6] = smgduan[h % 10], smg[6] |= 0X80; // 加上dp
    smg[5] = smgduan[(min / 10) % 10];
    smg[4] = smgduan[min % 10], smg[4] |= 0X80;
    smg[3] = smgduan[(sec / 10) % 10];
    smg[2] = smgduan[sec % 10], smg[2] |= 0X80;
    smg[1] = smgduan[(ssec / 100) % 10];
    smg[0] = smgduan[(ssec / 10) % 10]; // 10ms位
}

/*******************************************************************************
* 函 数 名      : DisplayDelay
* 函数功能      : 显示和延时函数
* 输    入      : unsigned int,unsigned char[0~7]为第0~7位数码管的显示数字
* 输    出      : 
*******************************************************************************/
void DisplayDelay(u8 smgxianshi[])
{
    u8 i;

    for (i = 0; i < 8; i++)
    {
        P0 = 0X00; //消隐
        switch (i) //位选，选择点亮的数码管，
        {
        case (7):
            LSA = 1;
            LSB = 1;
            LSC = 1;
            break; //显示第0位
        case (6):
            LSA = 0;
            LSB = 1;
            LSC = 1;
            break; //显示第1位
        case (5):
            LSA = 1;
            LSB = 0;
            LSC = 1;
            break; //显示第2位
        case (4):
            LSA = 0;
            LSB = 0;
            LSC = 1;
            break; //显示第3位
        case (3):
            LSA = 1;
            LSB = 1;
            LSC = 0;
            break; //显示第4位
        case (2):
            LSA = 0;
            LSB = 1;
            LSC = 0;
            break; //显示第5位
        case (1):
            LSA = 1;
            LSB = 0;
            LSC = 0;
            break; //显示第6位
        case (0):
            LSA = 0;
            LSB = 0;
            LSC = 0;
            break; //显示第7位
        }
        P0 = smgxianshi[i];
        Delay(85);
    }
}

/*******************************************************************************
* 函 数 名      : Timer0
* 函数功能      : 计数器0中断函数
* 输    入      : 
* 输    出      : 
*******************************************************************************/
void Timer0(void) interrupt 1
{
    sss += 1; // 记录+1次，18次为5ms

    if (sss == 18)
    {
        ssec += 5; // +5ms
        sss = 0;

        if (ssec == 1000)
        {
            sec += 1; // +1s
            ssec = 0;

            if (sec == 60)
            {
                min += 1; // +1min
                sec = 0;

                if (min == 60)
                {
                    h += 1; // +1h
                    min = 0;

                    if (h == 24)
                    {
                        h = 0; // 24h归零
                    }
                }
            }
        }
    }
}

// 2021年8月25号15点25分