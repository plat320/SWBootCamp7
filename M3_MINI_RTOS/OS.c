#include "device_driver.h"
#include "OS.h"

// 참고 : 최초 제공된 코드는 완전한 코드가 아님
//      그러므로 추후 RTOS 설계에 따라 보완이 필요함


/* Global Variable */
TCB tcb[MAX_TCB];
LinkedList TCBLink[MAX_TCB];
char stack[STACK_SIZE] __attribute__((__aligned__(8)));
TCB* current_tcb;

/* Function */
void OS_Init(void)
{
	TCBLink->head = NULL;

	int i;
	for(i=0; i<MAX_TCB; i++)
	{
		tcb[i].no_task = i;			// task 번호를 기반으로 접근할 일이 있을 것임
	}
}

char* _OS_Get_Stack(int size){
	static char* stack_limit = stack;
	static char* pstack = stack + STACK_SIZE;

	char* ret = pstack;

	size = (size + 7) & ~0x7;			// 8의 배수로 올림

	if(ret - size < stack_limit) return (char*)0;		// 할당했을 때 stack limit을 넘어가면 0 return
	pstack -= size;										// stack을 size만큼 줄임

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
	LinkedList *link;

	// task가 사용 할 TCB 할당
	if(idx_tcb >= MAX_TCB){
		return OS_FAIL_ALLOCATE_TCB;
	}
	ptcb = &tcb[idx_tcb];
	link = TCBLink;


	// task가 사용 할 stack 할당
	ptcb->top_of_stack = (unsigned long*)_OS_Get_Stack(size_stack);		// 분석해볼 것
	if(ptcb->top_of_stack == (unsigned long*)0)							// stack 할당 못받은 경우 null
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


	// linked list
	if (link->head == NULL){
		link->head = ptcb;
	}
	else{			// priority scan 후 낑가넣기
		TCB *current = link->head;
		while (prio <= current->prio || current->next != NULL){
			current = current->next;
		}
		if (current->next == NULL){
			current->next = ptcb;
		}
		else{
			ptcb->next = current->next;
			current->next = ptcb;
		}
	}

	return ptcb->no_task;
}

extern void _OS_Start_First_Task(void); // scheduler.s 파일 확인

void C_Scheduler(){
	int highest_prio = -1;
	int running_task_no = current_tcb->no_task;

	LinkedList *link;
	link = TCBLink;

}

void OS_Scheduler_Start(void)
{
	int i;

	// 현재는 선택된 첫 task의 실행만 진행하고 있음 (임의로 tcb[0]의 task를 현재 실행 할 태스크로 정의 (추후 정책에 따른 선택의 코드로 변경 필요)
	current_tcb = &tcb[0];

	// Exception Priority 초기화
	SCB->SHP[15 - 4] = 0xf << 4; // SysTick Exception Priority : Lowest Priority
	SCB->SHP[14 - 4] = 0xf << 4; // PendSV Exception Priority : Lowest Priority
	for(i = 0;i <= 42;i++)
	{
		NVIC_SetPriority(i, 0xe);
	}

	SysTick_OS_Tick(1);		// Systick Timer timeout이벤트 interrupt 활성화
	_OS_Start_First_Task();
}
