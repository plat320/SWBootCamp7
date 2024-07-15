#include "stm32f10x.h"
#include "option.h"
#include "macro.h"
#include "malloc.h"

extern void LED_Init(void);
extern void LED_Display(unsigned int num);
extern void LED_All_On(void);
extern void LED_All_Off(void);
extern void LED_0_Toggle(void);
extern void LED_1_Toggle(void);


// Uart.c

#define Uart_Init			Uart1_Init
#define Uart_Send_Byte		Uart1_Send_Byte
#define Uart_Send_String	Uart1_Send_String
#define Uart_Printf			Uart1_Printf

extern void Uart1_Init(int baud);
extern void Uart1_Send_Byte(char data);
extern void Uart1_Send_String(char *pt);
extern void Uart1_Printf(char *fmt,...);
extern void Uart1_RX_Interrupt_Enable(int en);
// Clock.c

extern void Clock_Init(void);

// Key.c

extern void Key_Poll_Init(void);
extern int Key_Get_Pressed(void);
extern void Key_Wait_Key_Released(void);
extern int Key_Wait_Key_Pressed(void);
extern  void Key_ISR_Enable(int en);


// Asm_Function.s

extern unsigned int __get_IPSR(void);

// Sys_Tick.c
extern void SysTick_OS_Tick(unsigned int msec);

// lcd.c
extern void Lcd_Init(void);
extern void Lcd_Set_Display_Mode(int mode);
extern void Lcd_Set_Cursor(unsigned short x, unsigned short y);
extern void Lcd_Set_Windows(unsigned short x1, unsigned short y1, unsigned short x2, unsigned short y2);
extern void Lcd_Put_Pixel(unsigned short x, unsigned short y, unsigned short color);
extern void Lcd_Clr_Screen(void);
extern void Lcd_Draw_Back_Color(unsigned short color);
extern void Lcd_Write_Data_16Bit(unsigned short color);
extern void Lcd_Draw_Box(int xs, int ys, int w, int h, unsigned short Color);
extern void TIM4_Repeat_Interrupt_Enable(int en, int time);
