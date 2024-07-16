#ifndef _OS_H_
#define _OS_H_

	/* [Constant] */
	#define MAX_TCB					(20)

	#define PRIO_HIGHEST			(0)
	#define PRIO_LOWEST				(10)
	#define NUM_PRIO				(PRIO_LOWEST - PRIO_HIGHEST + 1)

	#define OS_SUCCESS				(0)
	#define OS_FAIL_ALLOCATE_TCB	(-1)
	#define OS_FAIL_ALLOCATE_STACK	(-2)
	#define OS_FAIL_PUSH_QUEUE		(-3)
	#define OS_FAIL_POP_QUEUE		(-4)

	#define STACK_SIZE				(8 * 1024)

	#define STATE_READY				(0)
	#define STATE_BLOCKED			(1)

	#define INIT_PSR				(0x01000000)

	/* [ Type ] */

	typedef struct _tcb{
		unsigned long* top_of_stack;	// task 사용중인 stack의 top
		int no_task;					// task 번호 (tcb 배열의 index)
		int prio;						// task의 priority
		int state;						// task의 상태
	}TCB;

	/* [ Macro ] */

	/* [ Function ] */
	extern void OS_Init(void);
	extern int OS_Create_Task_Simple(void(*ptask)(void*), void* para, int prio, int size_stack);
	extern void OS_Scheduler_Start(void);

#endif
