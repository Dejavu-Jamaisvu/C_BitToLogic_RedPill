#include <stdio.h>

#define WINDOW_SIZE 5

typedef struct {
    float buffer[WINDOW_SIZE];
    int index; // 새로운 데이터가 저장될 위치이자, 가장 오래된 데이터의 위치
    int count;
    float sum;
} MovingAverageFilter;

// 초기화
void initFilter(MovingAverageFilter *f) {
    f->index = 0;
    f->count = 0;
    f->sum = 0.0f;
    for (int i = 0; i < WINDOW_SIZE; i++) f->buffer[i] = 0.0f;
}

float updateFilter(MovingAverageFilter *f, float input) {
    if (f->count == WINDOW_SIZE) {
        f->sum -= f->buffer[f->index];
    } else {
        f->count++; //최대 WINDOW_SIZE까지만 커짐
    }

    f->buffer[f->index] = input;
    f->sum += input;

    f->index = (f->index + 1) % WINDOW_SIZE;

    return f->sum / f->count;
}

int main() {
    MovingAverageFilter filter;
    initFilter(&filter);

    float inputs[] = {20.0, 22.0, 18.0, 25.0, 15.0, 20.0, 21.0, 19.0, 20.5, 20.0};
    int n = sizeof(inputs) / sizeof(inputs[0]);
    const char* notes[] = { // 이해를 위한 노트 하드코딩
        "(1개 평균)",
        "(2개 평균)",
        "(3개 평균: 20+22+18 / 3)",
        "",
        "(5개 꽉 참)",
        "(20.0이 들어오고, 맨 처음 20.0이 빠짐)",
        "(21.0이 들어오고, 22.0이 빠짐 -> 평균 하락)",
        "",
        "",
        ""
    };

    printf("=== Day 25: Moving Average Filter (Sliding Window) ===\n");
    printf("Window Size: %d\n\n", WINDOW_SIZE);
    printf("Step | Raw Input | Filtered Output\n");
    printf("-----+-----------+----------------\n");

    for (int i = 0; i < n; i++) {
        float output = updateFilter(&filter, inputs[i]);
        printf("%4d | %8.1f  | %10.1f  %s\n", i + 1, inputs[i], output, notes[i]);
    }

    return 0;
}