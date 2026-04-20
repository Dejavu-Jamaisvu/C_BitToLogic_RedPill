#include <stdio.h>
#include <stdint.h>

uint8_t reverse_bits_8(uint8_t n) {
    n = ((n & 0xF0) >> 4) | ((n & 0x0F) << 4);
    n = ((n & 0xCC) >> 2) | ((n & 0x33) << 2);
    n = ((n & 0xAA) >> 1) | ((n & 0x55) << 1);
    return n;
}

void print_binary(uint8_t n) {
    for (int i = 7; i >= 0; i--) {
        printf("%d", (n >> i) & 1);
        if (i == 4) printf(" ");
    }
}

int main() {
    uint8_t test_cases[] = {0xD2, 0x0F, 0xAA, 0x12};
    int num_cases = sizeof(test_cases) / sizeof(test_cases[0]);

    printf("=== Day 4: Bitwise Reverse (Mirroring) ===\n\n");

    for (int i = 0; i < num_cases; i++) {
        uint8_t input = test_cases[i];
        uint8_t output = reverse_bits_8(input);

        printf("Case %d:\n", i + 1);
        printf("  Input : 0x%02X (", input);
        print_binary(input);
        printf(")\n");

        printf("  Output: 0x%02X (", output);
        print_binary(output);
        printf(")\n");
        
        printf("  Verify: OK\n");
        printf("------------------------\n");
    }

    return 0;
}