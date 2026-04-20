#include <stdio.h>
#include <stdint.h>

// 매크로 정의
#define SET_BIT(val, pos)    ((val) | (1U << (pos)))
#define CLEAR_BIT(val, pos)  ((val) & ~(1U << (pos)))
#define TOGGLE_BIT(val, pos) ((val) ^ (1U << (pos)))
#define GET_BIT(val, pos)    (((val) >> (pos)) & 1U)

// 바이너리 출력
void print_binary(uint32_t n) {
    for (int i = 31; i >= 0; i--) {
        printf("%d", (n >> i) & 1);
        if (i % 4 == 0 && i != 0) printf(" ");
    }
}

int main() {
    uint32_t data = 0x12345678;

    printf("=== Day 1: Bitwise Macro Test ===\n");
    printf("[Init]   Hex: %#010X | Bin: ", data); // 0x%08X == %#010X // #을 붙이면 0x안해도 되지만 자리차지해서 8->10
    print_binary(data);
    printf("\n\n");

    // SET: 0번 비트 1로
    data = SET_BIT(data, 0);
    printf("[SET]    Target: Bit 0\n");
    printf("Result   Hex: %#010X | Bin: ", data);
    print_binary(data);
    printf("\n\n");

    // CLEAR: 4번 비트 0로
    data = CLEAR_BIT(data, 4);
    printf("[CLEAR]  Target: Bit 4\n");
    printf("Result   Hex: %#010X | Bin: ", data);
    print_binary(data);
    printf("\n\n");

    // TOGGLE: 3번 비트 반전
    data = TOGGLE_BIT(data, 3);
    printf("[TOGGLE] Target: Bit 3\n");
    printf("Result   Hex: %#010X | Bin: ", data);
    print_binary(data);
    printf("\n\n");

    // CHECK: 3번 비트 상태
    printf("[CHECK]  Bit 3 is currently: %X\n", GET_BIT(data, 3)); // %u 가능 // %b C23에서 가능

    return 0;
}