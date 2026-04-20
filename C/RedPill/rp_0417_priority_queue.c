#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int taskID;
    int priority;  // MinHeap: 숫자가 낮을수록 우선순위가 높음
} Task;

typedef struct {
    Task* heap;  // 태스크들을 저장할 동적 배열 (트리 구조를 배열로 표현)
    int size; // 배열의 몇번째 칸에 넣어야하는지, 상자가 비었는지 확인하는 용도
    int capacity; // 힙이 최대로 담을 수 있는 용량 // 오버플로우 방지용
} MinHeap;

MinHeap* createMinHeap(int capacity) {
    MinHeap* h = (MinHeap*)malloc(sizeof(MinHeap));
    h->capacity = capacity;
    h->size = 0;
    h->heap = (Task*)malloc(sizeof(Task) * capacity);
    return h;
}

void swap(Task* a, Task* b) {
    Task temp = *a;
    *a = *b;
    *b = temp;
}

void push(MinHeap* h, int id, int priority) {
    // 힙이 꽉 찼다면 삽입 중단
    // if (h->size == h->capacity) return;

    // 힙이 꽉 찼자면 크기 늘리기
    if (h->size == h->capacity) {
        h->capacity *= 2;
        // realloc: 기존 데이터를 유지하면서 메모리 공간만 늘려줌
        h->heap = (Task*)realloc(h->heap, sizeof(Task) * h->capacity);
    }
    
    int i = h->size++;
    h->heap[i].taskID = id;
    h->heap[i].priority = priority;

    while (i != 0 && h->heap[i].priority < h->heap[(i - 1) / 2].priority) {
        swap(&h->heap[i], &h->heap[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

Task pop(MinHeap* h) {
    Task root = h->heap[0];
    
    h->heap[0] = h->heap[--h->size];

    int i = 0;
    while (1) {
        int left = 2 * i + 1; 
        int right = 2 * i + 2;
        int smallest = i; // 현재 노드, 왼쪽 자식, 오른쪽 자식 중 가장 작은 값의 인덱스 저장용

        if (left < h->size && h->heap[left].priority < h->heap[smallest].priority)
            smallest = left;
        if (right < h->size && h->heap[right].priority < h->heap[smallest].priority)
            smallest = right;

        if (smallest != i) {
            swap(&h->heap[i], &h->heap[smallest]);
            i = smallest; 
        } else {
            break;
        }
    }
    return root; // 저장해둔 루트 반환
}

int main() {
    printf("=== Day 18: Task Scheduler (Min Heap) ===\n\n");

    Task inputData[] = {
        {1, 50}, {2, 10}, {3, 5}, {5, 0}, {4, 100}
    };
    
    int n = sizeof(inputData) / sizeof(inputData[0]);

    MinHeap* scheduler = createMinHeap(n);

    printf("Tasks pushed: ");
    for (int i = 0; i < n; i++) {
        printf("(%d, %d)%s", inputData[i].taskID, inputData[i].priority, (i == n - 1 ? "" : ", "));
        
        push(scheduler, inputData[i].taskID, inputData[i].priority);
    }
    printf("\n");

    printf("Processing Tasks...\n\n");

    while (scheduler->size > 0) {
        Task t = pop(scheduler);
        printf(">> Executing Task %d (Priority %d)\n", t.taskID, t.priority);
    }

    free(scheduler->heap);
    free(scheduler);

    return 0;
}