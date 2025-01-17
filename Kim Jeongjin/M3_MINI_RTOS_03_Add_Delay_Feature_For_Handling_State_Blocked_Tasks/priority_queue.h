#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

#include "OS.h"

	void pq_init(PriorityQueue* pq);
	void pq_push(PriorityQueue* pq, TCB* task, int (*compare)(TCB*, TCB*));
	TCB* pq_pop(PriorityQueue* pq, int (*compare)(TCB*, TCB*));
	TCB* pq_top(PriorityQueue* pq);
	void pq_remove(PriorityQueue* pq, TCB* task, int (*compare)(TCB*, TCB*));
	void pq_update(PriorityQueue* pq, TCB* task, int (*compare)(TCB*, TCB*));
	int pq_compare_ready(TCB* t1, TCB* t2);
	int pq_compare_delay(TCB* t1, TCB* t2);
	void pq_swap(TCB** a, TCB** b);

#endif // PRIORITY_QUEUE_H
