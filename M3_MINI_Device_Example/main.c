#include "device_driver.h"

extern volatile int systick_flag;	// stm32f10x_it.c - void SysTick_Handler(void)
extern volatile int tim4_timeout;	// stm32f10x_it.c - void TIM4_IRQHandler(void)
extern volatile int key_value;		// stm32f10x_it.c - void EXTI15_10_IRQHandler(void), void EXTI3_IRQHandler(void), void EXTI9_5_IRQHandler(void)
extern volatile int uart_rx_in;		// stm32f10x_it.c - void USART1_IRQHandler(void)
extern volatile char uart_rx_data;

void Main(void)
{
	// OS 없는 환경 상태에서의 Device 운영 example 코드

	Uart_Printf("M3-Mini Device Example\n");
	Uart_Printf("runtime.c - System_Init()의 Device 초기화 참고\n");

	for(;;)
	{
		if(uart_rx_in)
		{
			Uart_Printf("Uart Rx : %c\n", uart_rx_data);
			uart_rx_in = 0;
		}

		if(key_value)
		{
			Uart_Printf("Key Pushed : %d\n", key_value);
			key_value = 0;
		}

		if(tim4_timeout)
		{
			static int idx_color = 0;
			static int color[] = {0xf800,0x07e0,0x001f,0xffff};
			Lcd_Draw_Box(80, 60, 160, 120, color[idx_color]);
			idx_color = (idx_color + 1) % 4;
			tim4_timeout = 0;
		}

		if(systick_flag)
		{
			static int idx_func = 0;
			Uart_Printf("Systick timeout! : %d\n", idx_func++);

			systick_flag = 0;
		}
	}
}
