		ORG		0000H;下面那条指令放到0000H
		AJMP	START
		ORG		000BH;下面那条指令放到000BH
		AJMP	interrupt_1
		ORG		001BH;下面那条指令放到001BH
		AJMP	interrupt_3
		ORG 	0100H;下面那条指令放到0100H
START:
;参数定义，初始化
		NMS 		DATA	30H;定义叫做NMS的变量，用来延时1ms，放在30H
		N250MS 		DATA 	31H;定义叫做N250MS的变量，用来延时250ms，放在31H
		BianHua 	DATA 	32H;定义叫做BianHua的变量，用来设置LED变化次数，放在32H
		KEY 		DATA	33H;定义叫做KEY的变量，存放行列键盘扫描值，放在33H
		LED_Cyclic 	DATA	34H;定义叫做KEY的变量，记录LED循环次数，放在34H
		MOV 	R0,#0;A保护位
		MOV 	R1,#0;定时器标志记录位，只给定时器0用
		MOV 	R2,#0;LED查表偏移位
		MOV 	R3,#0;延时计数保护位

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

MAIN:
;主函数
		ACALL	Timer0Init;定时器0初始化
		ACALL	Timer1Init;定时器1初始化
MAIN_LOOP:
		MOV		BianHua,#8;变量BianHua赋值，n种变化
		MOV		N250MS,#1;延时250ms
		ACALL	DELAY_N250MS
		ACALL	LED_Cyclic_Display;LED显示
		AJMP	MAIN_LOOP;循环
		
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

Key_Scan:
;按键扫描函数		
		MOV		P2,#0FFH;写高用于检测
;判断行列键盘
		MOV		P2,#0F0H;判断列
		MOV		A,P2
		CJNE	A,#0F0H,KP2_I_Date_1;判断有无按键按下
		AJMP	Key_Scan_END
KP2_I_Date_1:
		CJNE	A,#070H,KP2_I_Date_2
		MOV		KEY,#1
		AJMP	KP2_L_Date_1
KP2_I_Date_2:
		CJNE	A,#0B0H,KP2_I_Date_3
		MOV		KEY,#2
		AJMP	KP2_L_Date_1
KP2_I_Date_3:
		CJNE	A,#0D0H,KP2_I_Date_4
		MOV		KEY,#3
		AJMP	KP2_L_Date_1
KP2_I_Date_4:
		MOV		KEY,#4

KP2_L_Date_1:
		MOV		P2,#00FH;判断行
		MOV		A,P2
		CJNE	A,#007H,KP2_L_Date_2
		MOV		A,KEY
		AJMP	Key_Scan_END
KP2_L_Date_2:
		CJNE	A,#00BH,KP2_L_Date_3
		MOV		A,KEY
		ADD		A,#4
		AJMP	Key_Scan_END
KP2_L_Date_3:
		CJNE	A,#00DH,KP2_L_Date_4
		MOV		A,KEY
		ADD		A,#8
		AJMP	Key_Scan_END
KP2_L_Date_4:
		MOV		A,KEY
		ADD		A,#12
Key_Scan_END:
		MOV		KEY,A
		
		RET
		
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

LED_Cyclic_Display:
;LED查表显示函数
		MOV 	A,R2;
		ADD		A,LED_Cyclic
		MOV 	DPTR,#TABLE0;查表0初始化
		MOVC 	A,@A+DPTR;查表
		MOV 	P0,A;将表中数据送入led0
		
		MOV 	A,R2;
		ADD		A,LED_Cyclic
		MOV 	DPTR,#TABLE1;查表1初始化
		MOVC 	A,@A+DPTR;查表
		MOV 	P1,A;将表中数据送入led1
		
		INC		LED_Cyclic;循环次数记录
		MOV		A,LED_Cyclic
		CJNE	A,BianHua,LED_Cyclic_Display_END
		MOV		LED_Cyclic,#0;循环次数归零
LED_Cyclic_Display_END:
		RET

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

Key_Data:
;按键数值处理函数
		MOV		A,KEY
	
		CJNE	A,#0,Key_Data_0
		AJMP	Key_Data_END
Key_Data_0:	
		CJNE	A,#1,Key_Data_1
		MOV		R2,#8
		AJMP	Key_Data_END
Key_Data_1:		
		CJNE	A,#2,Key_Data_2
		MOV		R2,#16
		AJMP	Key_Data_END
Key_Data_2:		
		CJNE	A,#3,Key_Data_3
		MOV		R2,#24
		AJMP	Key_Data_END
Key_Data_3:		
		CJNE	A,#4,Key_Data_4
		MOV		R2,#32
		AJMP	Key_Data_END
Key_Data_4:		
		CJNE	A,#5,Key_Data_5
		MOV		R2,#40
		AJMP	Key_Data_END
Key_Data_5:		
		CJNE	A,#6,Key_Data_6
		MOV		R2,#48
		AJMP	Key_Data_END
Key_Data_6:		
		CJNE	A,#7,Key_Data_7
		MOV		R2,#56
		AJMP	Key_Data_END
Key_Data_7:		
		CJNE	A,#8,Key_Data_8
		MOV		R2,#64
		AJMP	Key_Data_END
Key_Data_8:		
		CJNE	A,#9,Key_Data_9
		MOV		R2,#72
		AJMP	Key_Data_END
Key_Data_9:		
		CJNE	A,#10,Key_Data_10
		MOV		R2,#80
		AJMP	Key_Data_END
Key_Data_10:		
		CJNE	A,#11,Key_Data_11
		MOV		R2,#88
		AJMP	Key_Data_END
Key_Data_11:		
		CJNE	A,#12,Key_Data_12
		MOV		R2,#96
		AJMP	Key_Data_END
Key_Data_12:		
		CJNE	A,#13,Key_Data_13
		MOV		R2,#104
		AJMP	Key_Data_END
Key_Data_13:		
		CJNE	A,#14,Key_Data_14
		MOV		R2,#112
		AJMP	Key_Data_END
Key_Data_14:		
		CJNE	A,#15,Key_Data_15
		MOV		R2,#120
		AJMP	Key_Data_END
Key_Data_15:		
		CJNE	A,#16,Key_Data_END
		MOV		R2,#128
Key_Data_END:	
		RET

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

DELAY_NMS:
;定时器查询延时NMS函数
		CJNE 	R1,#4,$;判断R0是否为4，否则循环
		MOV 	R1,#0;是则复位R1
		
		DJNZ	NMS,DELAY_NMS;循环延时1ms，n次
		
		RET
		
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

DELAY_N250MS:
;延时N250MS函数
		MOV		NMS,#250
		ACALL	DELAY_NMS

		DJNZ	N250MS,DELAY_N250MS
		
		RET
		
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

Timer0Init:
;定时器0初始化
		ORL 	TMOD,#02H;设置定时器0工作方式为2，8位自动重装定时器
		MOV 	TL0,#06H;定时器0低八位赋初值，0.25ms延时
		MOV 	TH0,#06H;定时器0高八位赋初值，自动重装
		SETB 	ET0;定时器0中断打开
		SETB 	EA;总中断打开
		SETB 	TR0;控制定时器0
		
		RET

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

Timer1Init:
;定时器1初始化		
		ORL 	TMOD,#10H;设置定时器1工作方式为1，16位定时器
		MOV 	TL1,#0F0H;定时器1低八位赋初值，10ms延时
		MOV 	TH1,#0D8H;定时器1高八位赋初值，10ms延时
		SETB 	ET1;定时器1中断打开
		SETB 	EA;总中断打开
		SETB 	TR1;控制定时器1
		
		RET
		
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	
interrupt_1:
;定时器0中断
		INC R1;R1加一
		RETI
		
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

interrupt_3:
;定时器1中断
		MOV 	TL1,#0F0H;定时器1低八位赋初值，10ms延时
		MOV 	TH1,#0D8H;定时器1高八位赋初值，10ms延时
		ACALL	Key_Scan
		ACALL	Key_Data
;判断有无按键按下
		MOV		P2,#0F0H;
		MOV		A,P2
		CJNE	A,#0F0H,LED_Cyclic_RESET
		RETI
LED_Cyclic_RESET:
		MOV		LED_Cyclic,#0
		RETI

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

		ORG	2000H
TABLE0:
		DB	0FFH,0FFH,0FFH,0FFH,0FFH,0FFH,0FFH,0FFH
			
		DB	000H,0FFH,000H,0FFH,000H,0FFH,000H,0FFH
		DB	000H,080H,0C0H,0E0H,0F0H,0F8H,0FCH,0FEH
		DB	0AAH,055H,0AAH,055H,0AAH,055H,0AAH,055H
		DB	0FFH,0FFH,0FFH,0FFH,03FH,0CFH,0F3H,0FCH
			
		DB	000H,0FFH,000H,0FFH,000H,0FFH,000H,0FFH
		DB	000H,080H,0C0H,0E0H,0F0H,0F8H,0FCH,0FEH
		DB	0AAH,055H,0AAH,055H,0AAH,055H,0AAH,055H
		DB	0FFH,0FFH,0FFH,0FFH,03FH,0CFH,0F3H,0FCH
			
		DB	000H,0FFH,000H,0FFH,000H,0FFH,000H,0FFH
		DB	000H,080H,0C0H,0E0H,0F0H,0F8H,0FCH,0FEH
		DB	0AAH,055H,0AAH,055H,0AAH,055H,0AAH,055H
		DB	0FFH,0FFH,0FFH,0FFH,03FH,0CFH,0F3H,0FCH
			
		DB	000H,0FFH,000H,0FFH,000H,0FFH,000H,0FFH
		DB	000H,080H,0C0H,0E0H,0F0H,0F8H,0FCH,0FEH
		DB	0AAH,055H,0AAH,055H,0AAH,055H,0AAH,055H
		DB	0FFH,0FFH,0FFH,0FFH,03FH,0CFH,0F3H,0FCH

TABLE1:
		DB	0FFH,0FFH,0FFH,0FFH,0FFH,0FFH,0FFH,0FFH
			
		DB	000H,0FFH,000H,0FFH,000H,0FFH,000H,0FFH
		DB	000H,080H,0C0H,0E0H,0F0H,0F8H,0FCH,0FEH
		DB	0AAH,055H,0AAH,055H,0AAH,055H,0AAH,055H
		DB	03FH,0CFH,0F3H,0FCH,0FFH,0FFH,0FFH,0FFH
			
		DB	000H,0FFH,000H,0FFH,000H,0FFH,000H,0FFH
		DB	000H,080H,0C0H,0E0H,0F0H,0F8H,0FCH,0FEH
		DB	0AAH,055H,0AAH,055H,0AAH,055H,0AAH,055H
		DB	03FH,0CFH,0F3H,0FCH,0FFH,0FFH,0FFH,0FFH
			
		DB	000H,0FFH,000H,0FFH,000H,0FFH,000H,0FFH
		DB	000H,080H,0C0H,0E0H,0F0H,0F8H,0FCH,0FEH
		DB	0AAH,055H,0AAH,055H,0AAH,055H,0AAH,055H
		DB	03FH,0CFH,0F3H,0FCH,0FFH,0FFH,0FFH,0FFH

		DB	000H,0FFH,000H,0FFH,000H,0FFH,000H,0FFH
		DB	000H,080H,0C0H,0E0H,0F0H,0F8H,0FCH,0FEH
		DB	0AAH,055H,0AAH,055H,0AAH,055H,0AAH,055H
		DB	03FH,0CFH,0F3H,0FCH,0FFH,0FFH,0FFH,0FFH
			
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

		END