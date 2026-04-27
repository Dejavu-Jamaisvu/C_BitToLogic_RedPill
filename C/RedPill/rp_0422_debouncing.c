#include <stdio.h>

#define THRESHOLD 3

typedef struct {
    int counter;
    int stable_output;
} Debouncer;

void UpdateAndPrint(Debouncer* d, int raw, int step, const char* note) {
    if (raw != d->stable_output) {
        d->counter++;
        
        if (d->counter >= THRESHOLD) {
            d->stable_output = raw;
            d->counter = 0;
            
            printf("  >> [State Changed] to %d\n", d->stable_output);
        }
    } else {
        d->counter = 0;
    }

    printf("%4d | %5d     | %4d    | %7d", step, raw, d->counter, d->stable_output);
    if (note) printf("  %s", note);
    printf("\n");
}

int main() {
    Debouncer btn = {0, 0};
    int raw_inputs[] = {0, 0, 1, 0, 1, 1, 1, 1, 1, 0};
    const char* notes[] = { // 이해를 위한 하드코딩
        NULL, NULL, 
        "<-- 노이즈 발생 (카운트 시작)", 
        "<-- 다시 0 복귀 (카운트 리셋!)", 
        "<-- 진신호 시작", 
        NULL, 
        "<-- 3회 연속 성공으로 상태 변경", 
        NULL, NULL, 
        "<-- 노이즈 무시"
    };

    printf("=== Day 24: Button Debouncing Logic ===\n");
    printf("Condition: %d consecutive samples required.\n\n", THRESHOLD);
    printf("Step | Raw Input | Counter | Output (Stable)\n");
    printf("-----+-----------+---------+----------------\n");

    for (int i = 0; i < 10; i++) {
        UpdateAndPrint(&btn, raw_inputs[i], i + 1, notes[i]);
    }

    return 0;
}