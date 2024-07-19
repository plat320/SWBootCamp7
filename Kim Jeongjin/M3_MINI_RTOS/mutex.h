#ifndef _MUTEX_H_
#define _MUTEX_H_

#include "priority_queue.h"
#include "OS.h"

#define MAX_MUTEX     (3)

#define MUTEX_FULL	  (-1)

#define MUTEX_TAKE_SUCCESS	(0)
#define MUTEX_TAKE_FAIL		(-1)

typedef struct _mutex {
    TCB* owner;                     // Mutex owner task
    int locked;                     // Mutex locked state
    Queue waiting_queue;    // Tasks waiting for the mutex
} Mutex;

extern Mutex mutex[MAX_MUTEX];

void initMutex(void);
int createMutex(void);
int takeMutex(int mutex_id);
void giveMutex(int mutex_id);

#endif // _MUTEX_H_
