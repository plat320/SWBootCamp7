#include "device_driver.h"
#include "mutex.h"
#include "priority_queue.h"

Mutex* mutex_list[MAX_MUTEX];
// static 변수로 버퍼 관리
char mutex_buffer[MUTEX_BUFFER_SIZE] __attribute__((__aligned__(8)));
int scheduler_flag; // Flag for checking Scheduler Start

void Mutex_Init(void) {
    char* buffer = _Mutex_Get_Buffer(MAX_MUTEX * sizeof(Mutex));
    if (buffer == NULL) {
        Uart_Printf("Failed to allocate memory for mutex_list\n");
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
        mutex_list[i]->task_related = 0;
        mutex_list[i]->waiting_queue.front = NULL;
        mutex_list[i]->waiting_queue.rear = NULL;
        mutex_list[i]->waiting_queue.size = 0;
        mutex_list[i]->waiting_queue.data_size = 0;
        mutex_list[i]->waiting_queue.free_nodes = NULL;
    }
}

char* _Mutex_Get_Buffer(int size) {
    static char* buffer_limit = mutex_buffer;
    static char* pbuffer = mutex_buffer + MUTEX_BUFFER_SIZE;

    size = (size + 7) & ~0x7; // 8바이트 정렬

    if (pbuffer - size < buffer_limit) {
        return (char*)0; // 메모리 부족
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
            mutex_list[i]->task_related = task_related;
            createQueue(&mutex_list[i]->waiting_queue, sizeof(int), MAX_TCB, NO_ALLOCATED_TASK);
            return i; // Mutex 생성 성공, Mutex 인덱스 반환
        }
    }
    return FAIL_ALLOCATE_MUTEX; // 모든 Mutex가 사용 중인 경우
}

int Take_Mutex(int mutex_id) {
    if (mutex_id < 0 || mutex_id >= MAX_MUTEX) {
        return FAIL_TO_TAKE_MUTEX; // 유효하지 않은 mutex_id
    }

    if (scheduler_flag == SCHEDULER_NOT_START || mutex_list[mutex_id]->task_related == TASK_NOT_RELATED) {
    	if (mutex_list[mutex_id]->locked == 0) {
    		mutex_list[mutex_id]->locked = 1;
    		return SUCCESS_ALLOCATE_MUTEX;
    	}
        return FAIL_TO_TAKE_MUTEX;
    }

    if (mutex_list[mutex_id]->locked == 0) {
        mutex_list[mutex_id]->locked = 1;
        mutex_list[mutex_id]->no_task = current_tcb->no_task;
        current_tcb->waiting_for_mutex = NO_WAITING_MUTEX;
        //Uart_Printf("BBB : %d\n", current_tcb->no_task);
        return SUCCESS_ALLOCATE_MUTEX; // Mutex 획득 성공
    }

    if (scheduler_flag) {
    	if (tcb[mutex_list[mutex_id]->no_task].prio < current_tcb->prio) {
    	     tcb[mutex_list[mutex_id]->no_task].prio = current_tcb->prio;
    	     pq_update(&ready_queue, &tcb[mutex_list[mutex_id]->no_task], pq_compare_ready);
    	}
        // Task 관련 Mutex에 대한 처리
        if (current_tcb->waiting_for_mutex == mutex_id) {
        	//Uart_Printf("CCC\n");
            return FAIL_TO_TAKE_MUTEX; // 이미 대기 중인 경우
        }
        current_tcb->state = STATE_BLOCKED;
        current_tcb->waiting_for_mutex = mutex_id;
        enqueue(&mutex_list[mutex_id]->waiting_queue, current_tcb->no_task);
        //Uart_Printf("DDD : %d\n", current_tcb->no_task);
        OS_Pend_Trigger();
    }
    return FAIL_TO_TAKE_MUTEX;
}


void Give_Mutex(int mutex_id) {
    if (mutex_id < 0 || mutex_id >= MAX_MUTEX) {
        return; // 유효하지 않은 mutex_id
    }

    if (mutex_list[mutex_id]->task_related == TASK_NOT_RELATED) {
    	mutex_list[mutex_id]->locked = 0;
    	return;
    }

    if (scheduler_flag && mutex_list[mutex_id]->no_task != current_tcb->no_task) {
        return; // Mutex의 소유자가 아닌 경우
    }

    //Uart_Printf("AAA\n");
    if (!isEmpty(&mutex_list[mutex_id]->waiting_queue)) {
    	//Uart_Printf("cur_task give from %d\n", current_tcb->no_task);
        int next_tcb_no;
        dequeue(&mutex_list[mutex_id]->waiting_queue, &next_tcb_no, NO_ALLOCATED_TASK);
        //Uart_Printf("nxt_task give to %d\n", tcb[next_tcb_no].no_task);
        tcb[next_tcb_no].state = STATE_READY;
        tcb[next_tcb_no].waiting_for_mutex = NO_WAITING_MUTEX;
        pq_push(&ready_queue, &tcb[next_tcb_no], pq_compare_ready);
        mutex_list[mutex_id]->no_task = next_tcb_no;
    } else {
    	//Uart_Printf("no wait\n");
        mutex_list[mutex_id]->locked = 0;
        mutex_list[mutex_id]->no_task = NO_ALLOCATED_TASK;
    }

    if (scheduler_flag) {
        current_tcb->waiting_for_mutex = NO_WAITING_MUTEX;
        current_tcb->prio = current_tcb->base_prio; // Reset priority to base priority
        pq_update(&ready_queue, current_tcb, pq_compare_ready);
    }
}

void Set_Mutex_Scheduler_Flag() {
	scheduler_flag = SCHEDULER_START;
}
