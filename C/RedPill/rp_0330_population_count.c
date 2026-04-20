#include <stdio.h>

// [Naive] 루프 사용해 한 비트씩 확인
int count_naive(unsigned int n) {
    int count = 0;
    for (int i = 0; i < 32; i++) {
        if ((n >> i) & 1) count++;
    }
    return count;
}

// [Kernighan] 비트가 1인 개수만큼만 반복하는 최적화 알고리즘
int count_kernighan(unsigned int n) {
    int count = 0;
    while (n > 0) {
        n &= (n - 1); // 가장 오른쪽에 있는 1을 제거
        count++;
    }
    return count;
}

// [SWAR] 루프가 전혀 없는 비트 연산 방식
int count_swar(unsigned int n) {
    n = n - ((n >> 1) & 0x55555555);
    n = (n & 0x33333333) + ((n >> 2) & 0x33333333);
    n = (n + (n >> 4)) & 0x0F0F0F0F;
    n = n + (n >> 8);
    n = n + (n >> 16);
    return n & 0x0000003F; // 최대값 32를 읽기 위한 마스크
}

// [Built-in] 컴파일러 내장 함수
int count_builtin(unsigned int n) {
    return __builtin_popcount(n);
}

void print_case(int case_num, unsigned int input) {
    printf("Case %d: Input 0x%08X\n", case_num, input);
    printf("  [Naive]     : %d\n", count_naive(input));
    printf("  [Kernighan] : %d (Recommended Logic)\n", count_kernighan(input));
    printf("  [SWAR]      : %d (Strict Loop-free)\n", count_swar(input));
    printf("  [Built-in]  : %d\n", count_builtin(input));
    printf("------------------------------\n");
}

int main() {
    printf("=== Day 5: Population Count (Counting Set Bits) ===\n\n");

    print_case(1, 0x00000000);
    print_case(2, 0x00000007);
    print_case(3, 0x12345678);
    print_case(4, 0xFFFFFFFF);

    return 0;
}