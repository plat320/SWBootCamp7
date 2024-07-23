#include "device_driver.h"
#include "OS.h"

int dummyParams[10];

void Task1(void *para)
{
//	volatile int i;
	int cnt = 0;
//	int KeyValueReceiverIndex = OS_Create_Queue(sizeof(int), 10);
	KeyValueReceiverIndex = OS_Create_Queue(sizeof(int), 10);
//	Uart_Printf("*** KeyValueReceiverIndex: %d\n", KeyValueReceiverIndex);
//	char usart_received_data[32];
//	int UsartReceiverIndex = OS_Create_Queue(sizeof(usart_received_data), 5);
	for(;;)
	{
		Uart_Printf("Task3 : %d\n", cnt++);
		int received_data = -1;
    	int wait_result = OS_Signal_Wait(KeyValueReceiverIndex, &received_data, sizeof(int), 5000);

//    	Uart_Printf("KeyValueReceiverIndex: %d\n", KeyValueReceiverIndex);
//    	Uart_Printf("queues[0].size: %d\n", queues[0].size);
//    	Uart_Printf("queues[0].data_size: %d\n", queues[0].data_size);
//    	Uart_Printf("queues[1].size: %d\n", queues[1].size);
//    	Uart_Printf("queues[1].data_size: %d\n", queues[1].data_size);

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
//    		Uart_Printf("��������� ���� ����\n");
    		snake_object.head_direction = received_data;
//    		Calculate_Snake_Position(snake_object.head_direction);
    	}

    	/*
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
    	*/
    	OS_Block_Current_Task(500);
//		for(i=0;i<0x100000;i++);
	}
}

//void Task1(void *para)
//{
//	//volatile int i;
//	for(;;)
//	{
//		LED_0_Toggle();
//		//Uart_Printf("Task1\n");
//		OS_Block_Current_Task(500);
//		//Uart_Printf("Task1 after loop\n");
//	}
//}

void Task2(void *para)
{
	//volatile int i;
//	int cnt = 0;
	for(;;)
	{
		Calculate_Snake_Position(snake_object.head_direction);
		//Uart_Printf("Task2\n");
		OS_Block_Current_Task(500);
		//for(i=0;i<0x100000;i++);
		//Uart_Printf("Task2 after loop\n");
	}
}

void Task3(void *para)
{
	//volatile int i;
//	int cnt = 0;
	for(;;)
	{
		LED_1_Toggle();
		//Uart_Printf("Task2\n");
		OS_Block_Current_Task(100);
		//for(i=0;i<0x100000;i++);
		//Uart_Printf("Task2 after loop\n");
	}
}

//void Task2(void *para)
//{
//	//volatile int i;
////	int cnt = 0;
//	for(;;)
//	{
//		LED_1_Toggle();
//		//Uart_Printf("Task2\n");
//		OS_Block_Current_Task(100);
//		//for(i=0;i<0x100000;i++);
//		//Uart_Printf("Task2 after loop\n");
//	}
//}

//void Task3(void *para)
//{
////	volatile int i;
//	int cnt = 0;
////	int KeyValueReceiverIndex = OS_Create_Queue(sizeof(int), 10);
//	KeyValueReceiverIndex = OS_Create_Queue(sizeof(int), 10);
////	Uart_Printf("*** KeyValueReceiverIndex: %d\n", KeyValueReceiverIndex);
////	char usart_received_data[32];
////	int UsartReceiverIndex = OS_Create_Queue(sizeof(usart_received_data), 5);
//	for(;;)
//	{
//		Uart_Printf("Task3 : %d\n", cnt++);
//		int received_data = -1;
//    	int wait_result = OS_Signal_Wait(KeyValueReceiverIndex, &received_data, sizeof(int), 5000);
//
////    	Uart_Printf("KeyValueReceiverIndex: %d\n", KeyValueReceiverIndex);
////    	Uart_Printf("queues[0].size: %d\n", queues[0].size);
////    	Uart_Printf("queues[0].data_size: %d\n", queues[0].data_size);
////    	Uart_Printf("queues[1].size: %d\n", queues[1].size);
////    	Uart_Printf("queues[1].data_size: %d\n", queues[1].data_size);
//
//		Uart_Printf("Wait_result : %d\n", wait_result);
//    	if(wait_result == SIGNAL_TIMEOUT) {
//    		Uart_Printf("Signal Timeout\n");
//    	}
//    	else if(wait_result == SIGNAL_NO_PERMISSION) {
//    		Uart_Printf("Task 3 didn't create Queue\n");
//    	}
//    	else if(wait_result == SIGNAL_QUEUE_EMPTY) {
//    		Uart_Printf("Queue is empty\n");
//    	}
//    	else if(wait_result == SIGNAL_WRONG_DATA_TYPE) {
//    		Uart_Printf("Data Type is wrong\n");
//    	}
//    	else if(wait_result == SIGNAL_NO_ERROR){
//    		Uart_Printf("Received data is : %d\n", received_data);
////    		Uart_Printf("��������� ���� ����\n");
//    		snake_object.head_direction = received_data;
////    		Calculate_Snake_Position(snake_object.head_direction);
//    	}
//
//    	/*
//    	int usart_result = OS_Signal_Wait(UsartReceiverIndex, &usart_received_data, sizeof(usart_received_data), 5000);
//		Uart_Printf("usart_result : %d\n", usart_result);
//    	if(usart_result == SIGNAL_TIMEOUT) {
//    		Uart_Printf("Signal Timeout\n");
//    	}
//    	else if(usart_result == SIGNAL_NO_PERMISSION) {
//    		Uart_Printf("Task 3 didn't create Queue\n");
//    	}
//    	else if(usart_result == SIGNAL_QUEUE_EMPTY) {
//    		Uart_Printf("Queue is empty\n");
//    	}
//    	else if(usart_result == SIGNAL_WRONG_DATA_TYPE) {
//    		Uart_Printf("Data Type is wrong\n");
//    	}
//    	else if(usart_result == SIGNAL_NO_ERROR){
//    		Uart_Printf("Received data is : %s\n", usart_received_data);
//    	}
//    	*/
//    	OS_Block_Current_Task(500);
////		for(i=0;i<0x100000;i++);
//	}
//}

// �ӽ�
void Task5(void *para)
{
	for(;;)
	{
//		Calculate_Snake_Position(snake_object.head_direction);

//		Make_Target();

		// �ӽ� lcd
//		static int idx_color = 0;
//		static int color[] = {0xf800,0x07e0,0x001f,0xffff};
		// Lcd_Draw_Box(����, ����, ...)
//		Lcd_Draw_Box(80, 60, 160, 120, color[idx_color]);

//		Lcd_Draw_Box(40, 60, 20, 20, color[idx_color]);

//		Lcd_Draw_Box(40, 80, 20, 20, color[idx_color]);
//		Lcd_Draw_Box(80, 20, 20, 20, color[idx_color]);
//		Lcd_Draw_Box(40, 100, 20, 20, color[idx_color]);
//		Lcd_Draw_Box(140, 0, 20, 20, color[(idx_color + 1) % 4]);
//		Lcd_Draw_Box(140, 20, 20, 20, color[(idx_color + 1) % 4]);
//		Lcd_Draw_Box(140, 40, 20, 20, color[(idx_color + 1) % 4]);
//		Lcd_Draw_Box(140, 60, 20, 20, color[(idx_color + 1) % 4]);
//		Lcd_Draw_Box(140, 80, 20, 20, color[(idx_color + 1) % 4]);
//		Lcd_Draw_Box(160, 80, 20, 20, color[(idx_color + 1) % 4]);

//		Lcd_Draw_Box(260, 200, 20, 20, 0xf800);

//		idx_color = (idx_color + 1) % 4;
		OS_Block_Current_Task(500);
	}
}

void TaskDummy(void *para)
{
	//volatile int i;
	OS_Block_Current_Task(3000);
	for(;;)
	{
		// �ӽ� lcd
//		static int idx_color = 0;
//		static int color[] = {0xf800,0x07e0,0x001f,0xffff};
//		Lcd_Draw_Box(80, 60, 160, 120, color[idx_color]);
//		idx_color = (idx_color + 1) % 4;
//		OS_Block_Current_Task(3000);

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

	OS_Init();	// OS �ڷᱸ�� �ʱ�ȭ

	// �ӽ�
	Snake_Init();

//	OS_Create_Task_Simple(Task1, (void*)0, 5, 128);
	OS_Create_Task_Simple(Task1, (void*)0, 5, 1024);
	OS_Create_Task_Simple(Task2, (void*)0, 5, 1024);
	OS_Create_Task_Simple(Task3, (void*)0, 5, 1024);
//	OS_Create_Task_Simple(Task2, (void*)0, 5, 256); // Task ����
//	OS_Create_Task_Simple(Task3, (void*)0, 7, 1024);

	OS_Create_Task_Simple(Task5, (void*)0, 7, 1024);

	volatile int i;
	for(i = 4; i <= 60; i++)
	{
//		OS_Create_Task_Simple(TaskDummy, (void*)0, 5 + (i % 2), 128);
	}

	OS_Scheduler_Start();	// Scheduler Start (������ ù��° Task�� ���ุ �ϰ� ����)

	for(;;)
	{

	}
}