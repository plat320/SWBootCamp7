#include "device_driver.h"
#include "OS.h"
extern volatile int systick_flag;

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

	OS_Create_Task_Simple(Task2, (void*)0, 5, 128);
	OS_Create_Task_Simple(Task1, (void*)0, 5, 128);
	OS_Create_Task_Simple(Task3, (void*)0, 5, 128);
	// Task ����, stack size �м�, task �Լ� size + context size + ����.
	// UART PRINTF ����ϴ� �޸� ũ�� , build �ϰ� dumpall ���� �ڵ庸�� ������, ������ ���ָ� stack overflow �߻�
	// stack size 1kb�� �ϴ� ����
	SysTick_OS_Tick(1);
	OS_Scheduler_Start();	// Scheduler Start (������ ù��° Task�� ���ุ �ϰ� ����),
	// �ʱ� start �� task �ϳ� ����, ���������� svc ���(svc exception call) ����
	// �����ϳ��� ������Ѿ��� TCB�迭 0���� ����Ŵ
	// �ش� context restore�ϴ� �� �ۼ��Ǿ�����
	// ��� saving�ؾߵǴ��� �����ؾ���
//
	// ��� �ڷᱸ���� �ϸ� ���ڴ°�, �� �ڷᱸ���� OSINIT�� �ʱ�ȭ ,  Scheduler_test OS tick timer,  PendSV exception (systick timer�� ��û)
	for(;;)
	{
		;
/*		if(systick_flag)
		{
			Uart_Printf("Systick timeout! : %d\n", 1);
			systick_flag =0;
		}*/
	}
}
