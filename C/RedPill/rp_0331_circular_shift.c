#include <stdio.h>
#include <stdint.h>

// 왼쪽 원형 시프트
uint32_t rotate_left(uint32_t value, int n) {
    n %= 32; // n이 32보다 클 경우를 대비해 나머지 연산 처리
    if (n == 0) return value;
    return (value << n) | (value >> (32 - n));
}

// 오른쪽 원형 시프트
uint32_t rotate_right(uint32_t value, int n) {
    n %= 32;
    if (n == 0) return value;
    return (value >> n) | (value << (32 - n));
}

// 이진수 출력 보조
void print_binary(uint32_t n) {
    for (int i = 31; i >= 0; i--) {
        printf("%d", (n >> i) & 1);
        if (i % 4 == 0 && i != 0) printf(" ");
    }
}

int main() {
    uint32_t data = 0xF0000000;

    printf("=== Day 6: Circular Shift (Rotate) ===\n\n");

    printf("[Init]   Hex: 0x%08X\n", data);
    printf("         Bin: "); print_binary(data); 
    printf("\n\n");

    uint32_t rol_result = rotate_left(data, 4);
    printf("[ROL 4]  Hex: 0x%08X\n", rol_result);
    printf("         Bin: "); print_binary(rol_result);
    printf("\n         (MSB bits moved to LSB)\n\n");

    uint32_t ror_result = rotate_right(rol_result, 4);
    printf("[ROR 4]  Hex: 0x%08X\n", ror_result);
    printf("         Bin: "); print_binary(ror_result);
    printf("\n         (Restored to original)\n\n");

    uint32_t test2_data = 0x12345678;
    uint32_t test2_result = rotate_right(test2_data, 8);
    printf("[Test 2] Data: 0x%08X -> ROR 8 -> 0x%08X\n", test2_data, test2_result);

    return 0;
}