#include <stdio.h>

typedef enum {
    ADD = 0,
    SUB,
    MUL,
    DIV,
    EXIT,
    MAX_OPS // 관습적으로 목록에 총 몇 개의 항목이 있는지
} OpID;

// 함수 포인터 타입 정의
typedef int (*CalcFunc)(int, int);

int add(int a, int b) { return a + b; }
int sub(int a, int b) { return a - b; }
int mul(int a, int b) { return a * b; }
int div(int a, int b) { return (b != 0) ? a / b : 0; } // 0으로 나누기 방지

int main() {
    // 함수 포인터 배열 초기화 (enum 순서와 일치)
    CalcFunc operations[EXIT] = { add, sub, mul, div };
    
    int select, num1, num2;

    printf("=== Day 11: Function Pointer Array Calculator ===\n\n");

    while (1) {
        printf("Select (0:Add, 1:Sub, 2:Mul, 3:Div, 4:Exit): ");
        scanf("%d", &select);

        if (select == EXIT) break; 
        
        if (select >= ADD && select < EXIT) {
            printf("Input two integers: ");
            scanf("%d %d", &num1, &num2);

            // 함수 배열 인덱스로 함수 호출
            int result = operations[select](num1, num2);
            printf(">> Result: %d\n\n", result);
        }
    }

    return 0;
}