#include "device_driver.h"
#include "queue.h"
#include <string.h>

// static 변수로 버퍼 관리
char queue_buffer[QUEUE_BUFFER_SIZE] __attribute__((__aligned__(8)));

// 버퍼 관리 함수
char* _OS_Get_Buffer(int size) {
	static char* buffer_limit = queue_buffer;
	static char* pbuffer = queue_buffer + QUEUE_BUFFER_SIZE;

    size = (size + 7) & ~0x7; // 8바이트 정렬

    if (pbuffer - size < buffer_limit) {
        return (char*)0; // 메모리 부족
    }
    pbuffer -= size;

    return pbuffer;
}

// Queue 생성 함수
int createQueue(Queue* q, int data_size, int number_of_elements, int no_task) {
    q->front = NULL;
    q->rear = NULL;
    q->size = 0;
    q->data_size = data_size;
    q->no_task = no_task;
    q->max_size = number_of_elements;

    // 미리 할당된 메모리로 노드 초기화
    q->free_nodes = (Node*)_OS_Get_Buffer(sizeof(Node));
    if (q->free_nodes == NULL) {
        return QUEUE_FAIL_ALLOCATE;
    }
    if(number_of_elements == -1) {
    	number_of_elements = MAX_QUEUE_SIZE;
    }

    Node* current_node = q->free_nodes;
    int i;
    for (i = 0; i < number_of_elements - 1; ++i) {
        current_node->data = _OS_Get_Buffer(data_size);
        if (current_node->data == NULL) {
            return QUEUE_FAIL_ALLOCATE;
        }
        current_node->next = (Node*)_OS_Get_Buffer(sizeof(Node));
        if (current_node->next == NULL) {
            return QUEUE_FAIL_ALLOCATE;
        }
        current_node = current_node->next;
    }
    current_node->data = _OS_Get_Buffer(data_size);
    if (current_node->data == NULL) {
        return QUEUE_FAIL_ALLOCATE;
    }
    current_node->next = NULL;
    return QUEUE_SUCCESS;
}

// Queue에 데이터 추가 함수
int enqueue(Queue* q, const void* data) {
    if (isFull(q)) {
        return -1;
    }

    Node* new_node = q->free_nodes;
    q->free_nodes = q->free_nodes->next;

    memcpy(new_node->data, data, q->data_size);
    new_node->next = NULL;

    if (q->rear != NULL) {
        q->rear->next = new_node;
    }
    q->rear = new_node;

    if (q->front == NULL) {
        q->front = new_node;
    }

    q->size++;
    return 0;
}

// Queue에서 데이터 제거 함수
// no_task가 HAVE_PERMISSION(-1)이면 task_no 확인 비활성화
int dequeue(Queue* q, void* data, int no_task) {
    if (isEmpty(q)) {
        return DEQUEUE_EMPTY;
    }
    if (no_task != HAVE_PERMISSION && q->no_task != no_task) {
    	return DEQUEUE_NO_PERMISSION;
    }

//    Uart_Printf("--- 1 ---\n");
    Node* temp = q->front;
//    Uart_Printf("--- 2 ---\n");
//    Uart_Printf("q->front: %x\n", q->front);
//    Uart_Printf("((POINT*)q->front)->x: %d\n", ((POINT*)(q->front->data))->x);
//    Uart_Printf("q->size: %d\n", q->size);
//    Uart_Printf("data: %x\n", data);
//    Uart_Printf("temp->data: %x\n", temp->data);
//    Uart_Printf("q->data_size: %d\n", q->data_size);
    memcpy(data, temp->data, q->data_size);
//    Uart_Printf("--- 3 ---\n");
    q->front = q->front->next;
//    Uart_Printf("--- 4 ---\n");

    if (q->front == NULL) {
        q->rear = NULL;
    }

    temp->next = q->free_nodes;
    q->free_nodes = temp;

    q->size--;
    return DEQUEUE_SUCCESS;
}

// Queue가 비어 있는지 확인하는 함수
int isEmpty(Queue* q) {
    return (q->size == 0);
}

// Queue가 꽉 차 있는지 확인하는 함수
int isFull(Queue* q) {
    return (q->size == q->max_size);
}
