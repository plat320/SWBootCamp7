#ifndef _OS_H_
#define _OS_H_

#include "queue.h"
#include "snake.h"
#include "mutex.h"

	/* [Constant] */
	//#define MAX_TCB					(20)
	#define MAX_TCB					(60)
	#define MAX_QUEUE               (10)
	#define PQ_SIZE 				(MAX_TCB + 1)

	#define PRIO_HIGHEST			(0)
	#define PRIO_LOWEST				(10)
	#define NUM_PRIO				(PRIO_LOWEST - PRIO_HIGHEST + 1)

	#define OS_SUCCESS				(0)
	#define OS_FAIL_ALLOCATE_TCB	(-1)
	#define OS_FAIL_ALLOCATE_STACK	(-2)
	#define OS_FAIL_ALLOCATE_QUEUE (-3)

	#define STACK_SIZE				(5 * 1024)

	#define STATE_READY				(0)
	#define STATE_BLOCKED			(1)
	#define STATE_RUNNING			(2)

	#define SIGNAL_WRONG_DATA_TYPE	(-4)
	#define SIGNAL_QUEUE_EMPTY	   	(-3)
	#define SIGNAL_NO_PERMISSION    (-2)
	#define SIGNAL_TIMEOUT			(-1)
	#define SIGNAL_NO_ERROR			(0)

	#define SIGNAL_DEFAULT			(0)
	#define SIGNAL_WAIT				(1)
	#define SIGNAL_RECEIVED			(2)

	#define INIT_PSR				(0x01000000)

	/* [ Type ] */

	typedef struct _tcb{
		unsigned long* top_of_stack;	// task 사용중인 stack의 top
		int no_task;					// task 번호 (tcb 배열의 index)
		int prio;						// task의 priority
		int state;						// task의 상태

		long long int timestamp;
		long long int delay_until;
		int heap_index;
		int temp_value;
		int signal_flag;
		int base_prio;					// priority inheritence 이후 복귀할 priority
		int waiting_for_mutex;			// task가 기다리고 있는 mutex id, 없으면 -1
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
	extern Queue queues[MAX_QUEUE];
	extern long long int system_tick; // 시스템 타임스탬프
	extern int interrupt_period;
//	extern SNAKE_OBJECT snake_object;
	extern int KeyValueReceiverIndex;
	extern int ModeChangeIndex;
	extern int UpdateLcdIndex;
	extern int snake_mode;

	/* [ Macro ] */

	/* [ Function ] */
	void OS_Init(void);
	int OS_Create_Task_Simple(void(*ptask)(void*), void* para, int prio, int size_stack);
	int OS_Create_Queue(int data_size, int number_of_elements);
	extern void OS_Scheduler_Start(void);
	extern void OS_Scheduler(void);
	void PRINT_DUMMY(void);

	void OS_Tick(void);
	void OS_Pend_Trigger(void);

	int OS_Signal_Wait(int queue_no, void* buffer, int buffer_size, int timeout);
	void OS_Signal_Send(int queue_no, const void* buffer);

	void OS_Block_Current_Task(int delay);
	// void OS_Block_Task(int task_no, int delay);
	void OS_Unblock_Task(TCB* task);
	// void OS_Change_Priority(int task_no, int new_prio);

	void OS_Take_Mutex(void);
	void OS_Give_Mutex(void);

#endif
