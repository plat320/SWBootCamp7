#ifndef QUEUE_H
#define QUEUE_H

#include <stddef.h>

// 고정된 최대 크기 정의
#define MAX_QUEUE_SIZE          (10)
#define QUEUE_BUFFER_SIZE       (2 * 1024)

// Queue 상태 정의
#define QUEUE_SUCCESS           (0)
#define QUEUE_FAIL_ALLOCATE     (-1)

// DEQUEUE 상태 정의
#define DEQUEUE_SUCCESS				(0)
#define DEQUEUE_NO_PERMISSION		(-2)
#define DEQUEUE_EMPTY				(-3)

#define HAVE_PERMISSION			(-1)

// 노드 구조체 정의
typedef struct Node {
    void* data;
    struct Node* next;
} Node;

// Queue 구조체 정의
typedef struct Queue {
    Node* front;
    Node* rear;
    int size;      // 현재 Queue에 있는 요소의 수
    int data_size; // 데이터 크기
    Node* free_nodes; // 미리 할당된 노드들의 리스트
    int no_task; // Queue 생성한 task의 no
} Queue;

// 함수 선언
char* _OS_Get_Buffer(int size);
int createQueue(Queue* q, int data_size, int number_of_elements, int no_task);
int enqueue(Queue* q, const void* data);
int dequeue(Queue* q, void* data, int no_task);
int isEmpty(Queue* q);
int isFull(Queue* q);

// 버퍼 관리 함수
void queue_init(void);

#endif // QUEUE_H
