#include "device_driver.h"
#include "OS.h"
//#include "stm32f10x.h"
#include "priority_queue.h"
#include "queue.h"
//#include "snake.h"
#include <stdlib.h>

// 참고 : 최초 제공된 코드는 완전한 코드가 아님
//      그러므로 추후 RTOS 설계에 따라 보완이 필요함

/* Global Variable */
TCB tcb[MAX_TCB + 1];
char stack[STACK_SIZE] __attribute__((__aligned__(8)));
Queue queues[MAX_QUEUE];
TCB* current_tcb;
TCB* next_tcb;
PriorityQueue ready_queue;
PriorityQueue blocked_queue;
long long int system_tick = 0;
int interrupt_period = 100;
const int default_delay = 1000000000;
int os_mutex_id;

SNAKE_OBJECT snake_object;
int KeyValueReceiverIndex;
int ModeChangeIndex;
int UpdateLcdIndex;
int snake_mode;

int UsartReceiverIndex;
int IncredibleFlag = 0;
int KeyControlFlag = 0;
int TimerGap = 600;

/* Function */
void IdleTask(void *para) {
	volatile int i;
    for (;;) {
//    	Uart_Printf("IdleTask is working\n");
    	for(i=0;i<0x1000000;i++);
    }
}

void OS_Init(void)
{
	__set_BASEPRI(0x30);

	int i;
	for(i=0; i<=MAX_TCB; i++)
	{
		tcb[i].no_task = i;
		tcb[i].state = STATE_READY; // 초기 상태는 READY
		tcb[i].timestamp = 0;
		tcb[i].delay_until = 0;
		tcb[i].heap_index = -1;
		tcb[i].base_prio = 255;
	}
	pq_init(&ready_queue);
	pq_init(&blocked_queue);


	for(i=0; i<MAX_QUEUE; i++) {
	    queues[i].front = NULL;
	    queues[i].rear = NULL;
	    queues[i].size = 0;
	    queues[i].data_size = 0; // 초기화 추가
	    queues[i].free_nodes = NULL;
	}

	__set_BASEPRI(0x00);
	Uart_Printf("Create Mutex\n");
	Mutex_Init();
	os_mutex_id = Create_Mutex();
	Uart_Printf("Create IdleTask\n");
	OS_Create_Task_Simple(IdleTask, NULL, 255, 128);
	Uart_Printf("Os Init Success\n");
}

char* _OS_Get_Stack(int size){
	static char* stack_limit = stack;
	static char* pstack = stack + STACK_SIZE;

	char* ret = pstack;

	size = (size + 7) & ~0x7;

	if(ret - size < stack_limit) return (char*)0;
	pstack -= size;

	return ret;
}

int OS_Create_Task_Simple(void(*ptask)(void*), void* para, int prio, int size_stack)
{
	// ptask : task 코드의 시작주소
	// para : task코드가 시작하면서 전달받을 parameter
	// prio : 우선순위
	// size_stack : task가 사용할 stack의 할당 요청 사이즈
	__set_BASEPRI(0x30);
	static int idx_tcb = 0;
	TCB *ptcb;
	Uart_Printf("TCB[%d] will be created\n", idx_tcb);

	// task가 사용 할 TCB 할당
	if(idx_tcb > MAX_TCB)
	{
		return OS_FAIL_ALLOCATE_TCB;
	}
	ptcb = &tcb[idx_tcb];

	// task가 사용 할 stack 할당
	ptcb->top_of_stack = (unsigned long*)_OS_Get_Stack(size_stack);
	if(ptcb->top_of_stack == (unsigned long*)0)
	{
		return OS_FAIL_ALLOCATE_STACK;
	}

	idx_tcb++; // 다음 tcb 할당을 위한 index 이동

	// Task의 초기 context 정의
	ptcb->top_of_stack -= 16;
	ptcb->top_of_stack[8] = (unsigned long)para;
	ptcb->top_of_stack[14] = (unsigned long)ptask;
	ptcb->top_of_stack[15] = INIT_PSR;

    ptcb->prio = prio;
    ptcb->state = STATE_READY;
    ptcb->timestamp = system_tick; // 태스크 생성 시 타임스탬프 설정
    ptcb->heap_index = -1;

    // Add task to the priority queue
    pq_push(&ready_queue, ptcb, pq_compare_ready);

    Uart_Printf("TCB[%d] created with stack top at %p\n", idx_tcb - 1, ptcb->top_of_stack);

    __set_BASEPRI(0x00);
	return ptcb->no_task;
}

int OS_Create_Queue(int data_size, int number_of_elements) {
	__set_BASEPRI(0x30);

	int i;
    for (i = 0; i < MAX_QUEUE; i++) {
        if (queues[i].data_size == 0) { // 사용 중이지 않은 큐를 찾음
            if (createQueue(&queues[i], data_size, number_of_elements, current_tcb -> no_task) == QUEUE_SUCCESS) {
            	Uart_Printf("queues[%d] created \n", i);

            	__set_BASEPRI(0x00);
                return i; // 큐 생성 성공, 큐 인덱스 반환
            } else {
            	Uart_Printf("queue create fail \n", i);
            	__set_BASEPRI(0x00);
                return OS_FAIL_ALLOCATE_QUEUE; // 큐 생성 실패
            }
        }
    }
    Uart_Printf("No Queues memory \n", i);
    __set_BASEPRI(0x00);
    return OS_FAIL_ALLOCATE_QUEUE; // 모든 큐가 사용 중인 경우
}

extern void _OS_Start_First_Task(void); // scheduler.s 파일 확인

void OS_Scheduler_Start(void)
{
	__set_BASEPRI(0x30);
	int i;

	// 현재는 선택된 첫 task의 실행만 진행하고 있음 (임의로 tcb[0]의 task를 현재 실행 할 태스크로 정의 (추후 정책에 따른 선택의 코드로 변경 필요)
	current_tcb =  pq_pop(&ready_queue, pq_compare_ready);

	// Exception Priority 초기화
	SCB->SHP[15 - 4] = 0xf << 4; // SysTick Exception Priority : Lowest Priority
	SCB->SHP[14 - 4] = 0xf << 4; // PendSV Exception Priority : Lowest Priority
	for(i = 0;i <= 42;i++)
	{
		NVIC_SetPriority(i, 0xe);
	}

	current_tcb->state = STATE_RUNNING;

	SysTick_OS_Tick(interrupt_period);
	// TODO: 사망하면 이거 첫번째 인자 0으로 바꾸기
//	TIM4_Repeat_Interrupt_Enable(1, 600);	// TIM4 timeout 이벤트 interrupt 활성화

	__set_BASEPRI(0x00);
	Set_Mutex_Scheduler_Flag();
	_OS_Start_First_Task();
}

void OS_Scheduler(void)
{
	if (current_tcb->state == STATE_RUNNING){
		 current_tcb->state = STATE_READY;
		 current_tcb->timestamp = system_tick;
		 pq_push(&ready_queue, current_tcb, pq_compare_ready);
	}

	next_tcb = pq_top(&ready_queue);
	if (next_tcb == NULL) {

		return; // 우선순위 큐가 비어 있는 경우
	}
	else{
		pq_pop(&ready_queue, pq_compare_ready);
	    next_tcb->state = STATE_RUNNING;

	    current_tcb = next_tcb;
	}

}

void OS_Tick(void) {
	__set_BASEPRI(0x30);

    system_tick += interrupt_period;  // 시스템 타임스탬프 증가
    while (blocked_queue.size > 0 && pq_top(&blocked_queue)->delay_until <= system_tick) {
        TCB* task = pq_pop(&blocked_queue, pq_compare_delay);
        task->state = STATE_READY;
        pq_push(&ready_queue, task, pq_compare_ready);
    }

    __set_BASEPRI(0x00);
}

int OS_Signal_Wait(int queue_no, void* buffer, int buffer_size, int timeout) {
    __set_BASEPRI(0x30);

    int ret = SIGNAL_NO_ERROR;

    if (!(queue_no >= 0 && queue_no < MAX_QUEUE)) {
    	__set_BASEPRI(0x00);
    	return SIGNAL_NO_PERMISSION;
    }

    if (queues[queue_no].data_size != buffer_size) {
         __set_BASEPRI(0x00);
         return SIGNAL_WRONG_DATA_TYPE; // buffer 크기가 queue의 data_size와 일치하지 않음
    }

    if (current_tcb -> signal_flag != SIGNAL_RECEIVED){
        current_tcb -> signal_flag = SIGNAL_WAIT;
        OS_Block_Current_Task(timeout);
        __set_BASEPRI(0x30);
    }

    if(current_tcb -> signal_flag == SIGNAL_WAIT) {
        ret = SIGNAL_TIMEOUT;
        __set_BASEPRI(0x00);
        return ret;
    }
    else if (current_tcb -> signal_flag == SIGNAL_RECEIVED) {
        ret = dequeue(&queues[queue_no], buffer, current_tcb -> no_task);
        if(ret != DEQUEUE_SUCCESS) {
        	__set_BASEPRI(0x00);
        	return ret;
        }
    }
    else {
        Uart_Printf("SIGNAL Error, Need to check\n");
        ret = SIGNAL_NO_PERMISSION;
        __set_BASEPRI(0x00);
        return ret;
    }

    if (isEmpty(&queues[queue_no])){
        current_tcb -> signal_flag = SIGNAL_DEFAULT;
    }
    __set_BASEPRI(0x00);

    return ret;
}

void OS_Signal_Send(int queue_no, const void* buffer) {
	__set_BASEPRI(0x30);
	if (!(queue_no >= 0 && queue_no < MAX_QUEUE)) {
		return;
	}

	if (queues[queue_no].no_task >= 0 && queues[queue_no].no_task <= MAX_TCB) {
		TCB * target_tcb = &tcb[queues[queue_no].no_task];

		if(target_tcb -> signal_flag != SIGNAL_RECEIVED) {
			if (target_tcb -> signal_flag == SIGNAL_WAIT){
				OS_Unblock_Task(target_tcb);
				__set_BASEPRI(0x30);
			}
			target_tcb -> signal_flag = SIGNAL_RECEIVED;

		}

		enqueue(&queues[queue_no], buffer);
//		Uart_Printf("Size == %d\n", queues[queue_no].size);
	}

	__set_BASEPRI(0x00);
}

void OS_Block_Current_Task(int delay) {
	// 우리 보드는 상위 4비트만 사용하므로 상위 4비트에 우선순위를 설정해줘야 함
	__set_BASEPRI(0x30);

	pq_remove(&ready_queue, current_tcb, pq_compare_ready);

	current_tcb -> state = STATE_BLOCKED;
	if(delay == 0) {
		delay = default_delay;
	}
	current_tcb -> delay_until = system_tick + delay;

	pq_push(&blocked_queue, current_tcb, pq_compare_delay);

	OS_Pend_Trigger();
	__set_BASEPRI(0x00);
}

void OS_Unblock_Task(TCB* task) {
	__set_BASEPRI(0x30);

    if (task == NULL) {
    	return;
    }

    pq_remove(&blocked_queue, task, pq_compare_delay);

    task -> state = STATE_READY;
    task -> timestamp = system_tick; // 태스크 언블록 시 타임스탬프 갱신

    pq_push(&ready_queue, task, pq_compare_ready);

    __set_BASEPRI(0x00);
}


/*
void OS_Block_Task(int task_no, int delay) {
	__disable_irq();

    if (task_no < 0 || task_no > MAX_TCB) {
        return; // 유효하지 않은 task_no
    }

    TCB* task = &tcb[task_no];

    pq_remove(&ready_queue, task, pq_compare_ready);

    task->state = STATE_BLOCKED;
    task->delay_until = system_tick + delay;

    pq_push(&blocked_queue, task, pq_compare_delay);

    __enable_irq();
}

void OS_Change_Priority(int task_no, int new_prio) {
	__disable_irq();

    if (task_no >= 0 && task_no <= MAX_TCB) {
        tcb[task_no].prio = new_prio;
        pq_update(&ready_queue, &tcb[task_no], pq_compare_ready);
    }

   __enable_irq();
}
*/

void OS_Pend_Trigger(void) {
	Macro_Set_Bit(SCB->ICSR, 28);
}

void PRINT_DUMMY(void)
{
	Uart_Printf("No Problem\n");
}

