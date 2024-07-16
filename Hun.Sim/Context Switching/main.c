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
	// 참고 : Main 함수에 들어온 시점의 모드 관련 정보
	// Thread mode
	// Thread mode의 권한 : Priviliged
	// Thread mode의 MSP 사용 : 아직 RTOS의 초기화 과정이 남아 있으므로 MSP 사용하며 진행, 추후 Task 코드 실행 시 PSP 사용으로 전환

	Uart_Printf("M3-Mini RTOS\n");

	OS_Init();	// OS 자료구조 초기화

	OS_Create_Task_Simple(Task2, (void*)0, 5, 128);
	OS_Create_Task_Simple(Task1, (void*)0, 5, 128);
	OS_Create_Task_Simple(Task3, (void*)0, 5, 128);
	// Task 생성, stack size 분석, task 함수 size + context size + 마진.
	// UART PRINTF 사용하는 메모리 크기 , build 하고 dumpall 기계어 코드보고 역추적, 적당히 안주면 stack overflow 발생
	// stack size 1kb로 일단 설정
	SysTick_OS_Tick(1);
	OS_Scheduler_Start();	// Scheduler Start (지금은 첫번째 Task의 실행만 하고 있음),
	// 초기 start 시 task 하나 실행, 내부적으로 svc 명령(svc exception call) 실행
	// 변수하나가 실행시켜야할 TCB배열 0번를 가르킴
	// 해당 context restore하는 것 작성되어있음
	// 어떻게 saving해야되는지 구현해야함
//
	// 어떻게 자료구조를 하면 좋겠는가, 그 자료구조를 OSINIT에 초기화 ,  Scheduler_test OS tick timer,  PendSV exception (systick timer가 요청)
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
