#include <stdio.h>
#include <stdlib.h> // malloc, free

typedef void (*Callback)(int);

typedef struct TimerNode {
    int id;
    int dt; // 델타 타임 (앞 노드 만료 후 대기할 상대 시간)
    Callback callback;
    struct TimerNode* next; 
} TimerNode;


TimerNode* head = NULL; 


void PrintTimerList() {
    TimerNode* curr = head;
    int accumulated = 0; // 누적 시간 계산용
    printf("[Timer List] ");
    if (!curr) { printf("NULL\n"); return; }

    while (curr) {
        accumulated += curr->dt;
        printf("(ID:%d, dt:%d, total:%d)", curr->id, curr->dt, accumulated);
        if (curr->next) printf(" -> ");
        curr = curr->next;
    }
    printf(" -> NULL\n");
}

void SetTimer(int id, int ms, Callback cb) {
    TimerNode* newNode = (TimerNode*)malloc(sizeof(TimerNode));
    if (!newNode) return;

    newNode->id = id;
    newNode->callback = cb;

    printf("Timer %d set (%d ms) ", id, ms);

    TimerNode** pp = &head; 

    while (*pp != NULL && ms >= (*pp)->dt) {
        ms -= (*pp)->dt;
        pp = &((*pp)->next);
    }

    if (pp == &head) printf("[Inserted at HEAD]\n");
    else printf("[Inserted in List]\n");

    newNode->dt = ms;
    newNode->next = *pp; // pp가 가리키던 '다음 노드의 주소'를 내 다음으로 설정

    // 만약 내 뒤에 노드가 있다면, 그 노드의 dt를 내 시간만큼 줄여줌
    if (*pp != NULL) {
        (*pp)->dt -= ms;
    }

    // 이전 노드의 next(또는 head)가 나를 가리키도록 업데이트
    *pp = newNode; 

    PrintTimerList();
}


void Tick(int current_tick) {
    if (!head) return;

    head->dt--;

    if (head->dt > 0) {
        printf("Tick %d: Rem Head dt: %d\n", current_tick, head->dt);
    } else {
        printf("Tick %d: ", current_tick);
        while (head != NULL && head->dt <= 0) {
            TimerNode* expired = head;
            
            expired->callback(expired->id);
            
            head = head->next;
            free(expired); 
        }

        // 다음 대기 타이머가 있다면 남은 시간 출력
        if (head) printf("Rem Head dt: %d\n", head->dt);
        else printf("All timers cleared.\n");
    }
}

void on_timer_expired(int id) {
    printf(">> [Event] Timer %d expired! Action executed.\n", id);
}

int main() {
    printf("=== Day 22: Software Timer (Delta List / Malloc) ===\n\n");

    SetTimer(1, 10, on_timer_expired);
    SetTimer(2, 5, on_timer_expired);
    SetTimer(3, 15, on_timer_expired);

    printf("\n>> Start Ticking...\n");
    for (int i = 1; i <= 15; i++) {
        Tick(i);
    }

    return 0;
}