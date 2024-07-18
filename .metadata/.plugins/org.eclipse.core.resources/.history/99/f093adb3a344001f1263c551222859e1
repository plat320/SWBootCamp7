#include "device_driver.h"
#include "OS.h"

extern volatile int key_value;		// stm32f10x_it.c - void EXTI15_10_IRQHandler(void), void EXTI3_IRQHandler(void), void EXTI9_5_IRQHandler(void)
int dummyParams[10];

void Task1(void *para)
{
	//volatile int i;
	for(;;)
	{
		LED_0_Toggle();
		//Uart_Printf("Task1\n");
		OS_Block_Current_Task(500);
		//Uart_Printf("Task1 after loop\n");
	}
}

void Task2(void *para)
{
	//volatile int i;
	int cnt = 0;
	for(;;)
	{
		LED_1_Toggle();
		//Uart_Printf("Task2\n");
		if(key_value) {
			OS_Signal_Send(3, key_value);
			key_value = 0;
		}
		OS_Block_Current_Task(100);
		//for(i=0;i<0x100000;i++);
		//Uart_Printf("Task2 after loop\n");
	}
}

void Task3(void *para)
{
//	volatile int i;
	//int cnt = 0;
	for(;;)
	{
		//Uart_Printf("Task3 : %d\n", cnt++);
    	int received_data = OS_Signal_Wait(0);
    	if(received_data != SIGNAL_TIMEOUT) {
    		Uart_Printf("Received data is : %d\n", received_data);
    	}
    	else {
    		Uart_Printf("Signal Timeout\n");
    	}
    	OS_Block_Current_Task(500);
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
		//Uart_Printf("TaskDummy\n");
		//for(i=0;i<0x100000;i++);
		OS_Block_Current_Task(1000);
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
	OS_Create_Task_Simple(Task3, (void*)0, 7, 1024);
	volatile int i;
	for(i = 4; i <= 60; i++)
	{
		OS_Create_Task_Simple(TaskDummy, (void*)0, 5 + (i % 2), 128);
	}

	SysTick_OS_Tick(interrupt_period);
	OS_Scheduler_Start();	// Scheduler Start (지금은 첫번째 Task의 실행만 하고 있음)

	for(;;)
	{

	}
}
