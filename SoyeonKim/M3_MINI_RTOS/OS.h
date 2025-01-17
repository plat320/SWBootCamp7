#ifndef _OS_H_
#define _OS_H_

	/* [Constant] */
	//#define MAX_TCB					(20)
	#define MAX_TCB					(60)
	#define PQ_SIZE 				(MAX_TCB + 1)

	#define PRIO_HIGHEST			(0)
	#define PRIO_LOWEST				(10)
	#define NUM_PRIO				(PRIO_LOWEST - PRIO_HIGHEST + 1)

	#define OS_SUCCESS				(0)
	#define OS_FAIL_ALLOCATE_TCB	(-1)
	#define OS_FAIL_ALLOCATE_STACK	(-2)

	#define STACK_SIZE				(8 * 1024)

	#define STATE_READY				(0)
	#define STATE_BLOCKED			(1)
	#define STATE_RUNNING			(2)

	#define INIT_PSR				(0x01000000)

	/* [ Type ] */

	typedef struct _tcb{
		unsigned long* top_of_stack;	// task 사용중인 stack의 top
		int no_task;					// task 번호 (tcb 배열의 index)
		int prio;						// task의 priority
		int state;						// task의 상태

		// For Priority Queue
		long long int timestamp;
		long long int delay_until;
		int heap_index;
	}TCB;

	typedef struct {
	    TCB* heap[MAX_TCB + 1];
	    int size;
	} PriorityQueue;

	extern TCB tcb[MAX_TCB + 1];
	extern TCB* current_tcb;
	extern TCB* next_tcb;
	extern PriorityQueue ready_queue;
	extern PriorityQueue blocked_queue;
	extern long long int system_tick; // 시스템 타임스탬프
	extern int interrupt_period;

	/* [ Macro ] */

	/* [ Function ] */
	void OS_Init(void);
	int OS_Create_Task_Simple(void(*ptask)(void*), void* para, int prio, int size_stack);
	extern void OS_Scheduler_Start(void);
	extern void OS_Scheduler(void);
	void PRINT_DUMMY(void);

	void OS_Tick(void);
	void OS_Pend_Trigger(void);

	void OS_Block_Current_Task(int delay);
	// void OS_Block_Task(int task_no, int delay);
	// void OS_Unblock_Task(int task_no);
	// void OS_Change_Priority(int task_no, int new_prio);

#endif
