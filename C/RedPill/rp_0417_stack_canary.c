#include <stdio.h>
#include <stdlib.h> // exit() 함수
#include <string.h> // memset()

#define STACK_LIMIT 4096
#define CANARY_VALUE 0xDEADBEEF

void* stack_base = NULL;
unsigned int *canary_pos = NULL;

long get_stack_usage() {
    int current_var; // 현재 함수의 스택 프레임에 생성된 지역 변수
    return (long)stack_base - (long)&current_var;
}

void check_stack_canary() {
    long current_usage = get_stack_usage();
    
    printf("Current Stack Usage: %ld bytes\n", current_usage);

    if (current_usage > STACK_LIMIT || *canary_pos != CANARY_VALUE) {
        printf("\n[!!! WARNING !!!] Stack Overflow Detected!\n");
        printf("Limit: %d, Used: %ld\n", STACK_LIMIT, current_usage);
        printf("\n>> System survived. Returning safely.\n");
        exit(1); 
    }
}

void recursive_function(int depth) {
    char buffer[1000]; 
    memset(buffer, 0, sizeof(buffer)); // buffer를 전부 0으로 채워 확실히 사용함(최적화 방지)

    check_stack_canary();

    recursive_function(depth + 1);
}

int main() {
    int base_var; // 메인 함수 스택에 생성된 변수
    stack_base = &base_var; // 메인함수 스택의 시작점을 전역 포인터에 저장

    unsigned int canary = CANARY_VALUE;
    canary_pos = &canary; // 카나리의 주소를 전역 포인터에 저장

    printf("=== Day 19: Stack Overflow Detection (Canary Simulation) ===\n");
    printf("Stack Base Address: %p\n", stack_base);
    printf("Soft Limit: %d bytes\n\n", STACK_LIMIT);

    recursive_function(1);

    return 0;
}