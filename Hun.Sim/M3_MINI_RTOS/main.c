#include "device_driver.h"
#include "OS.h"
#include "draw_apple.h"
#include "lcd.h"

extern unsigned short *apple_img;
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
		OS_Block_Current_Task(100);
		//for(i=0;i<0x100000;i++);
		//Uart_Printf("Task2 after loop\n");
	}
}

void Task3(void *para)
{
//	volatile int i;
	int cnt = 0;
	int KeyValueReceiverIndex = OS_Create_Queue(sizeof(int), 10);
	char usart_received_data[32];
	int UsartReceiverIndex = OS_Create_Queue(sizeof(usart_received_data), 5);
	for(;;)
	{
		Uart_Printf("Task3 : %d\n", cnt++);
		int received_data = -1;
    	int wait_result = OS_Signal_Wait(KeyValueReceiverIndex, &received_data, sizeof(int), 5000);

		Uart_Printf("Wait_result : %d\n", wait_result);
    	if(wait_result == SIGNAL_TIMEOUT) {
    		Uart_Printf("Signal Timeout\n");
    	}
    	else if(wait_result == SIGNAL_NO_PERMISSION) {
    		Uart_Printf("Task 3 didn't create Queue\n");
    	}
    	else if(wait_result == SIGNAL_QUEUE_EMPTY) {
    		Uart_Printf("Queue is empty\n");
    	}
    	else if(wait_result == SIGNAL_WRONG_DATA_TYPE) {
    		Uart_Printf("Data Type is wrong\n");
    	}
    	else if(wait_result == SIGNAL_NO_ERROR){
    		Uart_Printf("Received data is : %d\n", received_data);
    	}

    	int usart_result = OS_Signal_Wait(UsartReceiverIndex, &usart_received_data, sizeof(usart_received_data), 5000);
		Uart_Printf("usart_result : %d\n", usart_result);
    	if(usart_result == SIGNAL_TIMEOUT) {
    		Uart_Printf("Signal Timeout\n");
    	}
    	else if(usart_result == SIGNAL_NO_PERMISSION) {
    		Uart_Printf("Task 3 didn't create Queue\n");
    	}
    	else if(usart_result == SIGNAL_QUEUE_EMPTY) {
    		Uart_Printf("Queue is empty\n");
    	}
    	else if(usart_result == SIGNAL_WRONG_DATA_TYPE) {
    		Uart_Printf("Data Type is wrong\n");
    	}
    	else if(usart_result == SIGNAL_NO_ERROR){
    		Uart_Printf("Received data is : %s\n", usart_received_data);
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
	// ���� : Main �Լ��� ���� ������ ��� ���� ����
	// Thread mode
	// Thread mode�� ���� : Priviliged
	// Thread mode�� MSP ��� : ���� RTOS�� �ʱ�ȭ ������ ���� �����Ƿ� MSP ����ϸ� ����, ���� Task �ڵ� ���� �� PSP ������� ��ȯ

	Uart_Printf("M3-Mini RTOS\n");

//	OS_Init();	// OS �ڷᱸ�� �ʱ�ȭ
//
//	OS_Create_Task_Simple(Task1, (void*)0, 5, 128);
//	OS_Create_Task_Simple(Task2, (void*)0, 5, 256); // Task ����
//	OS_Create_Task_Simple(Task3, (void*)0, 7, 1024);
//	volatile int i;
//	for(i = 4; i <= 60; i++)
//	{
//		OS_Create_Task_Simple(TaskDummy, (void*)0, 5 + (i % 2), 128);
//	}
//
//	OS_Scheduler_Start();	// Scheduler Start (������ ù��° Task�� ���ุ �ϰ� ����)

	Lcd_Draw_IMG(40, 40,  20,  20,  &apple_img);

	for(;;)
	{

	}
}