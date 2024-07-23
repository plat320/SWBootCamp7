#include "device_driver.h"
#include "mutex.h"
#include "priority_queue.h"

Mutex* mutex_list[MAX_MUTEX];
// static ������ ���� ����
char mutex_buffer[MUTEX_BUFFER_SIZE] __attribute__((__aligned__(8)));
int scheduler_flag; // Flag for checking Scheduler Start

void Mutex_Init(void) {
	static int initialized = 0;

	if (initialized) {
	    return; // �̹� �ʱ�ȭ�Ǿ���
	}
    char* buffer = _Mutex_Get_Buffer(MAX_MUTEX * sizeof(Mutex));
    if (buffer == NULL) {
        return;
    }

    int i;
    for (i = 0; i < MAX_MUTEX; i++) {
        mutex_list[i] = (Mutex*) (buffer + i * sizeof(Mutex));
    }

    scheduler_flag = SCHEDULER_NOT_START;

    for (i = 0; i < MAX_MUTEX; i++) {
    	mutex_list[i]->allocated = 0;
        mutex_list[i]->locked = 0;
        mutex_list[i]->waiting_queue.front = NULL;
        mutex_list[i]->waiting_queue.rear = NULL;
        mutex_list[i]->waiting_queue.size = 0;
        mutex_list[i]->waiting_queue.data_size = 0;
        mutex_list[i]->waiting_queue.free_nodes = NULL;
    }

    initialized = 1;
}

char* _Mutex_Get_Buffer(int size) {
    static char* buffer_limit = mutex_buffer;
    static char* pbuffer = mutex_buffer + MUTEX_BUFFER_SIZE;

    size = (size + 7) & ~0x7; // 8����Ʈ ����

    if (pbuffer - size < buffer_limit) {
        return (char*)0; // �޸� ����
    }
    pbuffer -= size;

    return pbuffer;
}

int Create_Mutex(int task_related) {
    int i;
    for (i = 0; i < MAX_MUTEX; i++) {
        if (mutex_list[i]->allocated == 0) {
        	mutex_list[i]->allocated = 1;
            mutex_list[i]->locked = 0;
            createQueue(&mutex_list[i]->waiting_queue, sizeof(int), MAX_TCB, NO_ALLOCATED_TASK);
            return i; // Mutex ���� ����, Mutex �ε��� ��ȯ
        }
    }
    return FAIL_ALLOCATE_MUTEX; // ��� Mutex�� ��� ���� ���
}

int Take_Mutex(int mutex_id, int task_related) {
    if (mutex_id < 0 || mutex_id >= MAX_MUTEX) {
        return FAIL_TO_TAKE_MUTEX; // ��ȿ���� ���� mutex_id
    }

    if (scheduler_flag == SCHEDULER_START && task_related == TASK_RELATED) {
        if (mutex_list[mutex_id]->locked == 0) {
            mutex_list[mutex_id]->locked = 1;
            mutex_list[mutex_id]->no_task = current_tcb->no_task;
            current_tcb->waiting_for_mutex = NO_WAITING_MUTEX;
            return SUCCESS_ALLOCATE_MUTEX;
        } else {
        	//Uart_Printf("scheduler_flag of current task %d is %d\n", current_tcb->no_task, scheduler_flag);
        	if(scheduler_flag == SCHEDULER_START) {
        		if (mutex_list[mutex_id]->no_task != NO_ALLOCATED_TASK && mutex_list[mutex_id]->no_task != current_tcb->no_task) {
        			return FAIL_TO_TAKE_MUTEX;
        		}
        		if (tcb[mutex_list[mutex_id]->no_task].prio < current_tcb->prio) {
        			tcb[mutex_list[mutex_id]->no_task].prio = current_tcb->prio;
        			pq_update(&ready_queue, &tcb[mutex_list[mutex_id]->no_task], pq_compare_ready);
        		}
        		if (current_tcb->waiting_for_mutex == mutex_id) {
        			return FAIL_TO_TAKE_MUTEX; // �̹� ��� ���� ���
        		}
                current_tcb->state = STATE_BLOCKED;
                current_tcb->waiting_for_mutex = mutex_id;
                int task_no = current_tcb->no_task;
                enqueue(&mutex_list[mutex_id]->waiting_queue, &task_no);
                OS_Pend_Trigger();
        	}
            return FAIL_TO_TAKE_MUTEX;
        }
    } else {
        if (mutex_list[mutex_id]->locked == 0) {
            mutex_list[mutex_id]->locked = 1;
            return SUCCESS_ALLOCATE_MUTEX;
        } else {
            return FAIL_TO_TAKE_MUTEX;
        }
    }
}

void Give_Mutex(int mutex_id, int task_related) {
    if (mutex_id < 0 || mutex_id >= MAX_MUTEX) {
        return; // ��ȿ���� ���� mutex_id
    }

    if (task_related && scheduler_flag) {
        if (mutex_list[mutex_id]->no_task != current_tcb->no_task) {
            return; // Mutex�� �����ڰ� �ƴ� ���
        }
        if (!isEmpty(&mutex_list[mutex_id]->waiting_queue)) {
            int next_tcb_no;
            dequeue(&mutex_list[mutex_id]->waiting_queue, &next_tcb_no, NO_ALLOCATED_TASK);
            tcb[next_tcb_no].state = STATE_READY;
            tcb[next_tcb_no].waiting_for_mutex = NO_WAITING_MUTEX;
            pq_push(&ready_queue, &tcb[next_tcb_no], pq_compare_ready);
            mutex_list[mutex_id]->no_task = next_tcb_no;
        } else {
            mutex_list[mutex_id]->locked = 0;
            mutex_list[mutex_id]->no_task = NO_ALLOCATED_TASK;
        }
        current_tcb->waiting_for_mutex = NO_WAITING_MUTEX;
        current_tcb->prio = current_tcb->base_prio;
        pq_update(&ready_queue, current_tcb, pq_compare_ready);
    } else {
        mutex_list[mutex_id]->locked = 0;
    }
}

void Set_Mutex_Scheduler_Flag() {
	scheduler_flag = SCHEDULER_START;
}
