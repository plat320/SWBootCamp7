#include "device_driver.h"
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <mutex.h>

static int uart_mutex_id = -1;

void Uart1_Init(int baud)
{
	double div;
	unsigned int mant;
	unsigned int frac;

	Macro_Set_Bit(RCC->APB2ENR, 2);
	Macro_Set_Bit(RCC->APB2ENR, 14);
	Macro_Write_Block(GPIOA->CRH, 0xff, 0x8a, 4);
	Macro_Set_Bit(GPIOA->ODR, 10);

	div = PCLK2/(16. * baud);
	mant = (int)div;
	frac = (int)((div - mant) * 16. + 0.5);
	mant += frac >> 4;
	frac &= 0xf;

	USART1->BRR = (mant<<4)+(frac<<0);
	USART1->CR1 = (1<<13)|(0<<12)|(0<<10)|(1<<3)|(1<<2);
	USART1->CR2 = 0<<12;
	USART1->CR3 = 0;

	uart_mutex_id = Create_Mutex();
}

void Uart1_Send_Byte(char data)
{
	if(data=='\n')
	{
		while(Macro_Check_Bit_Clear(USART1->SR, 7));
		USART1->DR = 0x0d;
	}

	while(Macro_Check_Bit_Clear(USART1->SR, 7));
	USART1->DR = data;
}

void Uart1_Send_String(char *pt)
{
	// Critical Section
	while(*pt!=0)
	{
		Uart1_Send_Byte(*pt++);
	}
}

void Uart1_Printf(char *fmt,...)
{
	va_list ap;
	char string[128];

	Take_Mutex(uart_mutex_id);

	va_start(ap,fmt);
	vsprintf(string,fmt,ap);
	Uart1_Send_String(string);
	va_end(ap);

	Give_Mutex(uart_mutex_id);
}

void Uart1_RX_Interrupt_Enable(int en)
{
	if(en)
	{
		Macro_Set_Bit(USART1->CR1, 5);
		NVIC_ClearPendingIRQ(37);
		NVIC_EnableIRQ(37);
	}
	else
	{
		Macro_Clear_Bit(USART1->CR1, 5);
		NVIC_DisableIRQ(37);
	}
}
