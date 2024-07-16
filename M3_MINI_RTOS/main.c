#include "device_driver.h"
#include "OS.h"

int dummyParams[10];

void Task1(void *para)
{
	volatile int i;
	for(;;)
	{
		LED_0_Toggle();
		//Uart_Printf("Task1\n");
		for(i=0;i<0x50000;i++);
		//Uart_Printf("Task1 after loop\n");
	}
}

void Task2(void *para)
{
	volatile int i;
	for(;;)
	{
		LED_1_Toggle();
		//Uart_Printf("Task2\n");
		for(i=0;i<0x100000;i++);
		//Uart_Printf("Task2 after loop\n");
	}
}

void Task3(void *para)
{
//	volatile int i;
	int cnt = 0;
	for(;;)
	{
    	OS_Block_Current_Task(2000);
		Uart_Printf("Task3 : %d\n", cnt++);
//		for(i=0;i<0x100000;i++);
	}
}

void TaskDummy(void *para)
{
	volatile int i;
	for(;;)
	{
		//Uart_Printf("Task4 : %d\n", cnt++);
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

	OS_Create_Task_Simple(Task1, (void*)0, 5, 128);
	OS_Create_Task_Simple(Task2, (void*)0, 5, 128); // Task ����
	OS_Create_Task_Simple(Task3, (void*)0, 5, 256);
	volatile int i;
	for(i = 4; i <= 60; i++)
	{
		//OS_Create_Task_Simple(TaskDummy, (void*)0, 5 + (i % 2), 128);
	}

	SysTick_OS_Tick(interrupt_period);
	OS_Scheduler_Start();	// Scheduler Start (������ ù��° Task�� ���ุ �ϰ� ����)

	for(;;)
	{

	}
}
