#include "device_driver.h"
#include "OS.h"
#include "command.h"

int dummyParams[10];

void Task1(void *para)
{
//	volatile int i;
//	int KeyValueReceiverIndex = OS_Create_Queue(sizeof(int), 10);
	KeyValueReceiverIndex = OS_Create_Queue(sizeof(int), 10);
//	Uart_Printf("*** KeyValueReceiverIndex: %d\n", KeyValueReceiverIndex);
//	char usart_received_data[32];
//	int UsartReceiverIndex = OS_Create_Queue(sizeof(usart_received_data), 5);
	for(;;)
	{
		int received_data = -1;
    	int wait_result = OS_Signal_Wait(KeyValueReceiverIndex, &received_data, sizeof(int), 0);

//    	Uart_Printf("KeyValueReceiverIndex: %d\n", KeyValueReceiverIndex);
//    	Uart_Printf("queues[0].size: %d\n", queues[0].size);
//    	Uart_Printf("queues[0].data_size: %d\n", queues[0].data_size);
//    	Uart_Printf("queues[1].size: %d\n", queues[1].size);
//    	Uart_Printf("queues[1].data_size: %d\n", queues[1].data_size);

    	//Uart1_Printf_From_Task("Task1 Wait_result : %d\n", wait_result);
    	if(wait_result == SIGNAL_TIMEOUT) {
    		Uart1_Printf_From_Task("Signal Timeout\n");
    	}
    	else if(wait_result == SIGNAL_NO_PERMISSION) {
    		Uart1_Printf_From_Task("Task 3 didn't create Queue\n");
    	}
    	else if(wait_result == SIGNAL_QUEUE_EMPTY) {
    		Uart1_Printf_From_Task("Queue is empty\n");
    	}
    	else if(wait_result == SIGNAL_WRONG_DATA_TYPE) {
    		Uart1_Printf_From_Task("Data Type is wrong\n");
    	}
    	else if(wait_result == SIGNAL_NO_ERROR){
    		//Uart1_Printf_From_Task("Received data is : %d\n", received_data);
    		// 기존 뱀 진행 방향의 반대 방향이 입력으로 들어오면 무시하고 그렇지 않은 경우에만 입력값으로 방향 업데이트
    		if (received_data * snake_object.snake_head_dir_pre != KEY_UP * KEY_DOWN
					&& received_data * snake_object.snake_head_dir_pre != KEY_LEFT * KEY_RIGHT
					&& received_data >=1 && received_data <= 4){
				snake_object.snake_head_dir = received_data;
			}
    		else {

    			OS_Signal_Send(ModeChangeIndex, (const void*)(&received_data));
    		}
    	}
	}
}


void Task2(void *para)
{
	ModeChangeIndex = OS_Create_Queue(sizeof(int), 10);
	for(;;)
	{
		int received_data = -1;
    	int wait_result = OS_Signal_Wait(ModeChangeIndex, &received_data, sizeof(int), 0);

    	if(wait_result == SIGNAL_TIMEOUT) {
    		Uart1_Printf_From_Task("Signal Timeout\n");
    	}
    	else if(wait_result == SIGNAL_NO_PERMISSION) {
    		Uart1_Printf_From_Task("Task 3 didn't create Queue\n");
    	}
    	else if(wait_result == SIGNAL_QUEUE_EMPTY) {
    		Uart1_Printf_From_Task("Queue is empty\n");
    	}
    	else if(wait_result == SIGNAL_WRONG_DATA_TYPE) {
    		Uart1_Printf_From_Task("Data Type is wrong\n");
    	}
    	else if(wait_result == SIGNAL_NO_ERROR){
    		Uart1_Printf_From_Task("START, %d %d\n", received_data, snake_mode);
    		if (received_data == 5 && snake_mode == MODE_INIT){
        		Uart1_Printf_From_Task("??? %d %d\n", received_data, snake_mode);

        		Lcd_Draw_Box(240, 135, 80, 105, 0);
    			TIM4_Repeat_Interrupt_Enable(1, 600);	// TIM4 timeout 이벤트 interrupt 활성화
        		Uart1_Printf_From_Task("??? %d %d\n", received_data, snake_mode);
    			snake_mode = MODE_START;
        		Uart1_Printf_From_Task("??? %d %d\n", received_data, snake_mode);
			}
    		else if (received_data == 5 && snake_mode == MODE_PAUSE){

    			Lcd_Draw_Box(240, 135, 80, 105, 0);
    			TIM4_Repeat_Interrupt_Enable(1, 600);	// TIM4 timeout 이벤트 interrupt 활성화
    			snake_mode = MODE_START;
			}
    		else if (received_data == 6 && snake_mode == MODE_START){
    			u8* s1 = "Press";
    			u8* s2 = "START";
    			u8* s3 = "BUTTON";
    			LCD_Show_String(12 *OBJECT_BLOCK_SIZE+12, 5 *OBJECT_BLOCK_SIZE +35 , 0x07e0,  0, 12, s1, 1);
    			LCD_Show_String(12 *OBJECT_BLOCK_SIZE+12, 7 *OBJECT_BLOCK_SIZE +25 , 0x07e0,  0, 12, s2, 1);
    			LCD_Show_String(12 *OBJECT_BLOCK_SIZE+5, 195, 0x07e0,  0, 12, s3, 1);
    			TIM4_Repeat_Interrupt_Enable(0, 600);	// TIM4 timeout 이벤트 interrupt 활성화
    			snake_mode = MODE_PAUSE;
    		}
    		else if (snake_mode == MODE_OVER){
    			int first_digit = snake_object.score%10;
    			int second_digit = snake_object.score/10;
    			u8* s1 = "FINAL SCORE ";
    			TIM4_Repeat_Interrupt_Enable(0, 600);	// TIM4 timeout 이벤트 interrupt 활성화
    			Lcd_Draw_Box(0, 0, 320, 240, 0);

    			Lcd_Draw_IMG(40, 70,  40,  40,  big_apple_img);
    			LCD_Show_String(90 , 70, 0x07e0,  0, 16, s1, 1);
				LCD_Show_Char(160, 120, 0x07e0,  0,  0x30 + first_digit, 16, 1);
				LCD_Show_Char(140, 120, 0x07e0,  0,  0x30 + second_digit, 16, 1);
    			//LCD_Show_String(12 *OBJECT_BLOCK_SIZE+12, 5 *OBJECT_BLOCK_SIZE +35 , 0x07e0,  0, 12, s1, 1);


    		}
    	}
	}

}

void Task3(void *para)
{
	Uart_Printf("*** KeyValueReceiverIndex: %d\n", KeyValueReceiverIndex);
	char usart_received_data[32];
	char changed_received_data[32];
	char poweroverwhelming[32] = "poweroverwhelming";
	char keycontrol[32] = "keycontrol";
	char normalmode[32] = "normalmode";
	char hardmode[32] = "hardmode";
	char hardestmode[32] = "hardestmode";
	UsartReceiverIndex = OS_Create_Queue(sizeof(usart_received_data), 5);
	volatile int i;
	const char keycommand[7] = {'r','w','s','a','d','o','p'};
	for(;;)
	{
    	int usart_result = OS_Signal_Wait(UsartReceiverIndex, &usart_received_data, sizeof(usart_received_data), 5000);
		Uart_Printf("usart_result : %d\n", usart_result);
    	if(usart_result == SIGNAL_TIMEOUT) {
    		Uart_Printf_From_Task("Signal Timeout\n");
    	}
    	else if(usart_result == SIGNAL_NO_PERMISSION) {
    		Uart_Printf_From_Task("Task 3 didn't create Queue\n");
    	}
    	else if(usart_result == SIGNAL_QUEUE_EMPTY) {
    		Uart_Printf_From_Task("Queue is empty\n");
    	}
    	else if(usart_result == SIGNAL_WRONG_DATA_TYPE) {
    		Uart_Printf_From_Task("Data Type is wrong\n");
    	}
    	else if(usart_result == SIGNAL_NO_ERROR){
    		my_tolower_str(usart_received_data, changed_received_data);
    		if (KeyControlFlag) {
    			if(my_strcasecmp(changed_received_data, &(keycommand[0])) == 0) {
    				KeyControlFlag = 0;
    				Uart_Printf_From_Task("Key Control Finished\n");
    			}
    			for(i = 1; i <= 6; i++) {
    				if(my_strcasecmp(changed_received_data, &(keycommand[i])) == 0) {
    					OS_Signal_Send(KeyValueReceiverIndex, (const void*)(&i));
    				}
    			}
    		}
    		else if (my_strcasecmp(changed_received_data, poweroverwhelming) == 0) {
    			IncredibleFlag ^= 1;
    		}
    		else if (my_strcasecmp(changed_received_data, keycontrol) == 0) {
    			KeyControlFlag = 1;
    			Uart_Printf_From_Task("Key Control Start\n");
    		}
    		else if (my_strcasecmp(changed_received_data, normalmode) == 0) {
    		    TimerGap = 600;
    		    Uart_Printf_From_Task("Hard Mode Start\n");
    		}
    		else if (my_strcasecmp(changed_received_data, hardmode) == 0) {
    			TimerGap = 450;
    		    Uart_Printf_From_Task("Hard Mode Start\n");
    		}
    		else if (my_strcasecmp(changed_received_data, hardestmode) == 0) {
    		    TimerGap = 300;
    		    Uart_Printf_From_Task("Hardest Mode Start\n");
    		}
    		else {
    			Uart_Printf_From_Task("Received data is : %s\n", usart_received_data);
    		}
    	}
	}
}

// 필요한 정보들 전달 받아서 LCD 구동
void Task5(void *para)
{
	UpdateLcdIndex = OS_Create_Queue(sizeof(int), 1);
	for(;;)
	{
		int received_data = -1;
		int wait_result = OS_Signal_Wait(UpdateLcdIndex, &received_data, sizeof(int), 0);

		if(wait_result == SIGNAL_TIMEOUT) {
			Uart1_Printf_From_Task("Signal Timeout\n");
		}
		else if(wait_result == SIGNAL_NO_PERMISSION) {
			Uart1_Printf_From_Task("Task 3 didn't create Queue\n");
		}
		else if(wait_result == SIGNAL_QUEUE_EMPTY) {
			Uart1_Printf_From_Task("Queue is empty\n");
		}
		else if(wait_result == SIGNAL_WRONG_DATA_TYPE) {
			Uart1_Printf_From_Task("Data Type is wrong\n");
		}
		else if(wait_result == SIGNAL_NO_ERROR){
//			Uart1_Printf_From_Task("Received data is : %d\n", received_data);
//    		Uart1_Printf_From_Task("여기까지는 정상 동작\n");
			Move_Snake_Position(snake_object.snake_head_dir);
			Lcd_Draw_Snake();
//    		Calculate_Snake_Position(snake_object.head_direction);
		}

//		OS_Block_Current_Task(500);
	}
}

void TaskDummy(void *para)
{
	//volatile int i;
	OS_Block_Current_Task(3000);
	for(;;)
	{
		// 임시 lcd
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
	// 참고 : Main 함수에 들어온 시점의 모드 관련 정보
	// Thread mode
	// Thread mode의 권한 : Priviliged
	// Thread mode의 MSP 사용 : 아직 RTOS의 초기화 과정이 남아 있으므로 MSP 사용하며 진행, 추후 Task 코드 실행 시 PSP 사용으로 전환

	Uart_Printf("M3-Mini RTOS\n");

	OS_Init();	// OS 자료구조 초기화

	// 임시
	Uart_Printf("Snake Init start\n");
	Snake_Init();
	Uart_Printf("Snake Init end\n");

	OS_Create_Task_Simple(Task1, (void*)0, 5, 1024);
	OS_Create_Task_Simple(Task2, (void*)0, 5, 1024);
	OS_Create_Task_Simple(Task3, (void*)0, 5, 1024);
	OS_Create_Task_Simple(Task5, (void*)0, 5, 1024);

	OS_Scheduler_Start();	// Scheduler Start (지금은 첫번째 Task의 실행만 하고 있음)

	for(;;)
	{

	}
}
