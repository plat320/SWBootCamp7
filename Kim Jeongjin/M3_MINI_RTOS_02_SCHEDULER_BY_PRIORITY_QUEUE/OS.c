#include "device_driver.h"
#include "OS.h"
#include "stm32f10x.h"
#include "priority_queue.h"
#include <stdlib.h>

// 참고 : 최초 제공된 코드는 완전한 코드가 아님
//      그러므로 추후 RTOS 설계에 따라 보완이 필요함


/* Global Variable */
TCB tcb[MAX_TCB];
char stack[STACK_SIZE] __attribute__((__aligned__(8)));
TCB* current_tcb;
TCB* next_tcb;
PriorityQueue ready_queue;
int current_stamp = 0;

/* Function */
void OS_Init(void)
{
	int i;
	for(i=0; i<MAX_TCB; i++)
	{
		tcb[i].no_task = i;
		tcb[i].state = STATE_READY; // 초기 상태는 READY
		tcb[i].next = NULL;
		tcb[i].timestamp = 0;
	}
	pq_init(&ready_queue);
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

	static int idx_tcb = 0;
	TCB *ptcb;
	Uart_Printf("TCB[%d] will be created\n", idx_tcb);

	// task가 사용 할 TCB 할당
	if(idx_tcb >= MAX_TCB)
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
    ptcb->next = NULL;
    ptcb->timestamp = current_stamp; // 태스크 생성 시 타임스탬프 설정

    // Add task to the priority queue
    pq_push(&ready_queue, ptcb);

    Uart_Printf("TCB[%d] created with stack top at %p\n", idx_tcb - 1, ptcb->top_of_stack);

	return ptcb->no_task;
}

extern void _OS_Start_First_Task(void); // scheduler.s 파일 확인

void OS_Scheduler_Start(void)
{
	int i;

	// 현재는 선택된 첫 task의 실행만 진행하고 있음 (임의로 tcb[0]의 task를 현재 실행 할 태스크로 정의 (추후 정책에 따른 선택의 코드로 변경 필요)
	current_tcb =  pq_pop(&ready_queue);

	// Exception Priority 초기화
	SCB->SHP[15 - 4] = 0xf << 4; // SysTick Exception Priority : Lowest Priority
	SCB->SHP[14 - 4] = 0xf << 4; // PendSV Exception Priority : Lowest Priority
	for(i = 0;i <= 42;i++)
	{
		NVIC_SetPriority(i, 0xe);
	}

	current_tcb->state = STATE_RUNNING;

	_OS_Start_First_Task();
	current_stamp++;
}

void OS_Scheduler(void)
{
	next_tcb = pq_top(&ready_queue);
	if (next_tcb == NULL) {
		Uart_Printf("next_tcb->no_task : NULL\n");
		return; // 우선순위 큐가 비어 있는 경우
	}
	//Uart_Printf("next_tcb->no_task : %d\n", next_tcb->no_task);

	//Uart_Printf("current_tcb->no_task : %d\n", current_tcb->no_task);
	//Uart_Printf("next_tcb->no_task : %d\n", next_tcb->no_task);
	if (next_tcb != NULL && next_tcb != current_tcb) {
		pq_pop(&ready_queue);
		//Uart_Printf("YES\n");
	    current_tcb->state = STATE_READY;
	    //Uart_Printf("current_tcb->state : %d\n", current_tcb->state);
	    next_tcb->state = STATE_RUNNING;
	    //Uart_Printf("next_tcb->state : %d\n\n\n", next_tcb->state);
	    current_tcb->timestamp = current_stamp;
	    pq_push(&ready_queue, current_tcb);
	    current_tcb = next_tcb;
	}
	current_stamp++;
}

/*
void OS_Block_Current_Task(void) {
    current_tcb->state = STATE_BLOCKED;
}

void OS_Unblock_Task(int task_no) {
    if (task_no >= 0 && task_no < MAX_TCB) {
        tcb[task_no].state = STATE_READY;
        tcb[task_no].timestamp = current_stamp; // 태스크 언블록 시 타임스탬프 갱신
        pq_push(&ready_queue, &tcb[task_no]);
    }
}
*/

void PRINT_DUMMY(void)
{
	Uart_Printf("No Problem\n");
}

