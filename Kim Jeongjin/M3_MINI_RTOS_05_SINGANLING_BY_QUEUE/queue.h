#ifndef QUEUE_H
#define QUEUE_H

#include <stddef.h>

// 고정된 최대 크기 정의
#define MAX_QUEUE_SIZE          (10)
#define QUEUE_BUFFER_SIZE       (2 * 1024)

// Queue 상태 정의
#define QUEUE_SUCCESS           (0)
#define QUEUE_FAIL_ALLOCATE     (-1)

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
} Queue;

// 함수 선언
char* _OS_Get_Buffer(int size);
int createQueue(Queue* q, int data_size);
int enqueue(Queue* q, void* data);
void dequeue(Queue* q, void* data);
int isEmpty(Queue* q);
int isFull(Queue* q);

// 버퍼 관리 함수
void queue_init(void);

#endif // QUEUE_H
