#include "device_driver.h"
#include "mutex.h"
#include "priority_queue.h"

Mutex* mutex_list[MAX_MUTEX];
// static 변수로 버퍼 관리
char mutex_buffer[MUTEX_BUFFER_SIZE] __attribute__((__aligned__(8)));
int scheduler_flag; // Flag for checking Scheduler Start

void Mutex_Init(void) {
	static int initialized = 0;

	if (initialized) {
	    return; // 이미 초기화되었음
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
            createQueue(&mutex_list[i]->waiting_queue, sizeof(int), MAX_TCB, NO_ALLOCATED_TASK);
            return i; // Mutex 생성 성공, Mutex 인덱스 반환
        }
    }
    return FAIL_ALLOCATE_MUTEX; // 모든 Mutex가 사용 중인 경우
}

int Take_Mutex(int mutex_id, int task_related) {
    __set_BASEPRI(0x30);
    if (mutex_id < 0 || mutex_id >= MAX_MUTEX) {
        __set_BASEPRI(0x00);
        return FAIL_TO_TAKE_MUTEX; // 유효하지 않은 mutex_id
    }
    if (mutex_list[mutex_id]->locked == 0) {
    	mutex_list[mutex_id]->locked = 1;
    	mutex_list[mutex_id]->no_task = current_tcb->no_task;
    	__set_BASEPRI(0x00);
    	return SUCCESS_ALLOCATE_MUTEX;
    }

    if (scheduler_flag == SCHEDULER_START && task_related == TASK_RELATED) {
    	int cur_task_no = current_tcb->no_task;
    	if(mutex_list[mutex_id]->no_task == cur_task_no) {
    		__set_BASEPRI(0x00);
    		return SUCCESS_ALLOCATE_MUTEX;
    	}
    	else {
    		//if (tcb[mutex_list[mutex_id]->no_task].prio < tcb[cur_task_no].prio) {
    		//    	tcb[mutex_list[mutex_id]->no_task].prio = tcb[cur_task_no].prio;
    		//    	pq_update(&ready_queue, &tcb[mutex_list[mutex_id]->no_task], pq_compare_ready);
    		//}
    		tcb[cur_task_no].state = STATE_BLOCKED;
    		tcb[cur_task_no].waiting_for_mutex = mutex_id;
    		int task_no = cur_task_no;
    		enqueue(&mutex_list[mutex_id]->waiting_queue, &task_no);
    		__set_BASEPRI(0x00);
    		OS_Pend_Trigger();
    		return SUCCESS_ALLOCATE_MUTEX;
    	}
    } else {
    	__set_BASEPRI(0x00);
        while (mutex_list[mutex_id]->locked == 1) {
            // Non-task related 획득 시 바쁜 대기
        }
        __set_BASEPRI(0x30);
        mutex_list[mutex_id]->locked = 1;
        __set_BASEPRI(0x00);
        return SUCCESS_ALLOCATE_MUTEX;
    }
}

void Give_Mutex(int mutex_id, int task_related) {
	__set_BASEPRI(0x30);
    if (mutex_id < 0 || mutex_id >= MAX_MUTEX) {
    	__set_BASEPRI(0x00);
        return; // 유효하지 않은 mutex_id
    }

    if (task_related && scheduler_flag == SCHEDULER_START) {
        if (mutex_list[mutex_id]->no_task != current_tcb->no_task) {
        	__set_BASEPRI(0x00);
            return; // Mutex의 소유자가 아닌 경우
        }

        if (!isEmpty(&mutex_list[mutex_id]->waiting_queue)) {
            int next_tcb_no;
            dequeue(&mutex_list[mutex_id]->waiting_queue, &next_tcb_no, NO_ALLOCATED_TASK);
            tcb[next_tcb_no].state = STATE_READY;
            tcb[next_tcb_no].waiting_for_mutex = NO_WAITING_MUTEX;
            pq_push(&ready_queue, &tcb[next_tcb_no], pq_compare_ready);
            mutex_list[mutex_id]->locked = 1;
            mutex_list[mutex_id]->no_task = next_tcb_no;
            __set_BASEPRI(0x00);
            OS_Pend_Trigger();
            __set_BASEPRI(0x30);
        } else {
            mutex_list[mutex_id]->locked = 0;
            mutex_list[mutex_id]->no_task = NO_ALLOCATED_TASK;
        }
        current_tcb->waiting_for_mutex = NO_WAITING_MUTEX;
        current_tcb->prio = current_tcb->base_prio;
        //pq_push(&ready_queue, current_tcb, pq_compare_ready);
    } else {
        mutex_list[mutex_id]->locked = 0;
    }
    __set_BASEPRI(0x00);
}

void Set_Mutex_Scheduler_Flag() {
	scheduler_flag = SCHEDULER_START;
}
