#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define BUFFER_SIZE 5

volatile int buffer[BUFFER_SIZE];
volatile int head = 0;
volatile int tail = 0;
volatile int count = 0;

void produce(int *item_id) {
    if (count < BUFFER_SIZE) {
        buffer[head] = *item_id;
        printf("[PROD] Produced Item %d (Head: %d, Count: %d)\n", *item_id, (head + 1) % BUFFER_SIZE, count + 1);
        head = (head + 1) % BUFFER_SIZE;
        count++;
        (*item_id)++;
    } else {
        printf("  >> [Buffer Full!] Producer waits... (Count: %d)\n", count);
    }
}

void consume() {
    if (count > 0) {
        int item = buffer[tail];
        printf("[CONS] Consumed Item %d (Tail: %d, Count: %d)\n", item, (tail + 1) % BUFFER_SIZE, count - 1);
        tail = (tail + 1) % BUFFER_SIZE;
        count--;
    } else {
        printf("  >> [Buffer Empty!] Consumer waits... (Count: %d)\n", count);
    }
}

int main() {
    srand((unsigned int)time(NULL));
    int item_id = 1;

    printf("=== Day 26: Producer-Consumer Simulation ===\n");
    printf("Buffer Size: %d\n\n", BUFFER_SIZE);

    for (int i = 0; i < 10; i++) { // 10번의 사이클 동안 여러 번 생산 및 소비 반복
        // 무작위 횟수 생산 (0~3번)
        int p_burst = rand() % 4; 
        for (int j = 0; j < p_burst; j++) {
            produce(&item_id);
        }

        // 무작위 횟수 소비 (0~3번)
        int c_burst = rand() % 4;
        for (int j = 0; j < c_burst; j++) {
            consume();
        }
        
    }

    return 0;
}