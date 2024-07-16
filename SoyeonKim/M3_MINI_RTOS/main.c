#include "device_driver.h"
#include "OS.h"

extern volatile int systick_flag;	// stm32f10x_it.c - void SysTick_Handler(void)

void Task1(void *para)
{
	volatile int i;
	for(;;)
	{
		LED_0_Toggle();
		for(i=0;i<0x50000;i++);
	}
}

void Task2(void *para)
{
	volatile int i;
	for(;;)
	{
		LED_1_Toggle();
		for(i=0;i<0x100000;i++);
	}
}

void Task3(void *para)
{
	volatile int i;
	int cnt = 0;
	for(;;)
	{
		Uart_Printf("Task3 : %d\n", cnt++);
		for(i=0;i<0x100000;i++);
	}
}

void Main(void)
{
	// ���� : Main �Լ��� ���� ������ ��� ���� ����
	// Thread mode
	// Thread mode�� ���� : Priviliged
	// Thread mode�� MSP ��� : ���� RTOS�� �ʱ�ȭ ������ ���� �����Ƿ� MSP ����ϸ� ����, ���� Task �ڵ� ���� �� PSP ������� ��ȯ

	Uart_Printf("M3-Mini RTOS\n");

	OS_Init();	// OS �ڷᱸ�� �ʱ�ȭ

//	for(;;)
//	{
//		if(systick_flag)
//		{
//			static int idx_func = 0;
//			Uart_Printf("Systick timeout! : %d\n", idx_func++);
//
//			systick_flag = 0;
//		}
//	}

	OS_Create_Task_Simple(Task1, (void*)0, 5, 128); // Task ����
	OS_Create_Task_Simple(Task2, (void*)0, 5, 128); // Task ����
	OS_Create_Task_Simple(Task3, (void*)0, 5, 128); // Task ����

	OS_Scheduler_Start();	// Scheduler Start (������ ù��° Task�� ���ุ �ϰ� ����)

	for(;;)
	{

	}
}