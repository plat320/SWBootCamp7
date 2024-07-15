#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

#include "OS.h"

	void pq_init(PriorityQueue* pq);
	void pq_push(PriorityQueue* pq, TCB* task);
	TCB* pq_pop(PriorityQueue* pq);
	TCB* pq_top(PriorityQueue* pq);

#endif // PRIORITY_QUEUE_H
