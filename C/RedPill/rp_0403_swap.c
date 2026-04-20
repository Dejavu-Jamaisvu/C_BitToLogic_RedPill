#include <stdio.h>
#include <stdint.h>

void my_swap(void *a, void *b, size_t size) {
    uint8_t *p1 = (uint8_t *)a;
    uint8_t *p2 = (uint8_t *)b;
    uint8_t temp;

    for (size_t i = 0; i < size; i++) {
        temp = *(p1 + i);
        *(p1 + i) = *(p2 + i);
        *(p2 + i) = temp;
    }
}

int main() {
    // 정수 교환
    int num1 = 10, num2 = 20;
    printf("[Integer Swap]\n");
    printf("Before: a = %d, b = %d\n", num1, num2);
    
    my_swap(&num1, &num2, sizeof(int));
    
    printf("After : a = %d, b = %d\n\n", num1, num2);

    // 실수 교환
    double d1 = 1.23, d2 = 9.87;
    printf("[Double Swap]\n");
    printf("Before: d1 = %.2f, d2 = %.2f\n", d1, d2);
    
    my_swap(&d1, &d2, sizeof(double));
    
    printf("After : d1 = %.2f, d2 = %.2f\n", d1, d2);

    return 0;
}