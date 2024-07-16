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
	// 참고 : Main 함수에 들어온 시점의 모드 관련 정보
	// Thread mode
	// Thread mode의 권한 : Priviliged
	// Thread mode의 MSP 사용 : 아직 RTOS의 초기화 과정이 남아 있으므로 MSP 사용하며 진행, 추후 Task 코드 실행 시 PSP 사용으로 전환

	Uart_Printf("M3-Mini RTOS\n");

	OS_Init();	// OS 자료구조 초기화

	OS_Create_Task_Simple(Task1, (void*)0, 5, 128);
	OS_Create_Task_Simple(Task2, (void*)0, 5, 128); // Task 생성
	OS_Create_Task_Simple(Task3, (void*)0, 5, 256);
	volatile int i;
	for(i = 4; i <= 60; i++)
	{
		//OS_Create_Task_Simple(TaskDummy, (void*)0, 5 + (i % 2), 128);
	}

	SysTick_OS_Tick(interrupt_period);
	OS_Scheduler_Start();	// Scheduler Start (지금은 첫번째 Task의 실행만 하고 있음)

	for(;;)
	{

	}
}
