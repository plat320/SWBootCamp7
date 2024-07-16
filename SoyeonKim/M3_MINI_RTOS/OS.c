#include "device_driver.h"
#include "OS.h"

// 참고 : 최초 제공된 코드는 완전한 코드가 아님
//      그러므로 추후 RTOS 설계에 따라 보완이 필요함


/* Global Variable */
TCB tcb[MAX_TCB];
char stack[STACK_SIZE] __attribute__((__aligned__(8)));
TCB* current_tcb;

/* Function */
void OS_Init(void)
{
	int i;
	for(i=0; i<MAX_TCB; i++)
	{
		tcb[i].no_task = i;
	}
}

char* _OS_Get_Stack(int size){
	static char* stack_limit = stack;
	static char* pstack = stack + STACK_SIZE;

	char* ret = pstack;

	// 올림해서 8의 배수로 만듦
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

	return ptcb->no_task;
}

extern void _OS_Start_First_Task(void); // scheduler.s 파일 확인

void OS_Scheduler_Start(void)
{
	int i;

	// 현재는 선택된 첫 task의 실행만 진행하고 있음 (임의로 tcb[0]의 task를 현재 실행 할 태스크로 정의 (추후 정책에 따른 선택의 코드로 변경 필요)
	current_tcb = &tcb[0];

	// Exception Priority 초기화
	SCB->SHP[15 - 4] = 0xf << 4; // SysTick Exception Priority : Lowest Priority
	SCB->SHP[14 - 4] = 0xf << 4; // PendSV Exception Priority : Lowest Priority
	// interrupt exception들의 priority 변경
	for(i = 0;i <= 42;i++)
	{
		NVIC_SetPriority(i, 0xe);
	}

	// Systick 동작시킴
	SysTick_OS_Tick(1);	// Systick Timer timeout이벤트 interrupt 활성화

	_OS_Start_First_Task();
}

void OS_Scheduler(void) {
//    int highest_prio = PRIO_LOWEST + 1;
//    TCB* highest_tcb = 0;
//    for(int i = 0; i < MAX_TCB; i++) {
//        if(tcb[i].state == STATE_READY && tcb[i].prio < highest_prio) {
//            highest_prio = tcb[i].prio;
//            highest_tcb = &tcb[i];
//        }
//    }
//    if(highest_tcb && highest_tcb != current_tcb) {
//        next_tcb = highest_tcb;
//        SCB->ICSR |= SCB_ICSR_PENDSVSET_Msk;
//    }
	static int __tmp_idx_tcb = 1;
	current_tcb = &tcb[__tmp_idx_tcb%3];
	__tmp_idx_tcb++;
}
