#include "device_driver.h"
#include "OS.h"

int dummyParams[10];

void Task1(void *para)
{
	//volatile int i;
	for(;;)
	{
		//LED_0_Toggle();
		//Uart_Printf("Task1: The quick brown fox jumps over the lazy dog in the park.\n");
		Uart_Printf_From_Task("Task1: The quick brown fox jumps over the lazy dog in the park.\n");
		OS_Block_Current_Task(1);
		//Uart_Printf("Task1 after loop\n");
	}
}

void Task2(void *para)
{
	//volatile int i;
	for(;;)
	{
		//LED_1_Toggle();
		//Uart_Printf("Task2: A journey of a thousand miles begins with a single step.\n");
		Uart_Printf_From_Task("Task2: A journey of a thousand miles begins with a single step.\n");
		OS_Block_Current_Task(1);
		//for(i=0;i<0x100000;i++);
		//Uart_Printf("Task2 after loop\n");
	}
}

void Task3(void *para)
{
//	volatile int i;
	//int cnt = 0;
	//int KeyValueReceiverIndex = OS_Creates_Queue(sizeof(int), 10);
	//char usart_received_data[32];
	//int UsartReceiverIndex = OS_Create_Queue(sizeof(usart_received_data), 5);
	for(;;)
	{
		//Uart_Printf("Task3: To be yourself in a world that is constantly changing you.\n");
		Uart_Printf_From_Task("Task3: To be yourself in a world that is constantly changing you.\n");
		OS_Block_Current_Task(1);
//		for(i=0;i<0x100000;i++);
	}
}

void TaskDummy(void *para)
{
	//volatile int i;
	OS_Block_Current_Task(3000);
	for(;;)
	{
		//((void(*)(void))0xE1234567)();
		Uart_Printf_From_Task("TaskDummy\n");
		//for(i=0;i<0x100000;i++);
		OS_Block_Current_Task(1000);
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

	OS_Create_Task_Simple(Task1, (void*)0, 5, 1024);
	OS_Create_Task_Simple(Task2, (void*)0, 6, 1024); // Task ����
	OS_Create_Task_Simple(Task3, (void*)0, 7, 1024);
	volatile int i;
	for(i = 4; i <= 60; i++)
	{
		//OS_Create_Task_Simple(TaskDummy, (void*)0, 5 + (i % 2), 1024);
	}

	OS_Scheduler_Start();	// Scheduler Start (������ ù��° Task�� ���ุ �ϰ� ����)

	for(;;)
	{

	}
}
