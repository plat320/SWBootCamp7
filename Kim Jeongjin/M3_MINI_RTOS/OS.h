#ifndef _OS_H_
#define _OS_H_

	/* [Constant] */
	//#define MAX_TCB					(20)
	#define MAX_TCB					(64)
	#define PQ_SIZE 				(MAX_TCB)

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
		unsigned long* top_of_stack;	// task ������� stack�� top
		int no_task;					// task ��ȣ (tcb �迭�� index)
		int prio;						// task�� priority
		int state;						// task�� ����

		// For Priority Queue
		int timestamp;
		int heap_index;
	}TCB;

	typedef struct {
	    TCB* heap[MAX_TCB];
	    int size;
	} PriorityQueue;

	extern TCB tcb[MAX_TCB];
	extern TCB* current_tcb;
	extern TCB* next_tcb;
	extern PriorityQueue ready_queue;
	extern int system_tick; // �ý��� Ÿ�ӽ�����

	/* [ Macro ] */

	/* [ Function ] */
	extern void OS_Init(void);
	extern int OS_Create_Task_Simple(void(*ptask)(void*), void* para, int prio, int size_stack);
	extern void OS_Scheduler_Start(void);
	extern void OS_Scheduler(void);
	extern void PRINT_DUMMY(void);

	/*
	void OS_Block_Current_Task(void);
	void OS_Unblock_Task(int task_no);
	*/

#endif
