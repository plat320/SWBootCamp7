#ifndef _MUTEX_H_
#define _MUTEX_H_

#include "queue.h"
#include "OS.h"

#define MAX_MUTEX 					(10)
#define MUTEX_BUFFER_SIZE       	(1 * 1024)

#define NO_ALLOCATED_TASK			(-1)

#define SUCCESS_ALLOCATE_MUTEX 		(0)
#define FAIL_ALLOCATE_MUTEX 		(-1)
#define FAIL_TO_TAKE_MUTEX 			(-2)
#define ALREADY_WAITING_MUTEX 		(-3)

#define SCHEDULER_START				(1)
#define SCHEDULER_NOT_START			(0)

#define NO_WAITING_MUTEX			(-1)

typedef struct _mutex {
    int no_task;                   // Mutex owner task_no
    int locked;                    // Mutex locked state
    Queue waiting_queue;           // Tasks waiting for the mutex
} Mutex;

extern Mutex* mutex_list[MAX_MUTEX];
extern char mutex_buffer[MUTEX_BUFFER_SIZE];
extern int scheduler_flag;

void Mutex_Init(void);
char* _Mutex_Get_Buffer(int size);
int Create_Mutex();
int Take_Mutex(int mutex_id);
void Give_Mutex(int mutex_id);
void Set_Mutex_Scheduler_Flag(void);

#endif
