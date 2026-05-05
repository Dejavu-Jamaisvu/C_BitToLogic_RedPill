#include <stdio.h>
#include <stdint.h>
#include <string.h>

#define POLYNOMIAL 0xEDB88320u

uint32_t crc32_bitwise(const uint8_t *data, size_t length) {
    uint32_t crc = 0xFFFFFFFFu; 

    for (size_t i = 0; i < length; i++) {
        crc ^= data[i];
        for (int j = 0; j < 8; j++) {
            if (crc & 1) {
                crc = (crc >> 1) ^ POLYNOMIAL;
            } else {
                crc >>= 1;
            }
        }
    }
    return crc ^ 0xFFFFFFFFu; 
}

uint32_t crc32_table[256];

void init_crc32_table() {
    for (uint32_t i = 0; i < 256; i++) {
        uint32_t crc = i;
        for (int j = 0; j < 8; j++) {
            if (crc & 1) {
                crc = (crc >> 1) ^ POLYNOMIAL;
            } else {
                crc >>= 1;
            }
        }
        crc32_table[i] = crc;
    }
}

uint32_t crc32_table_based(const uint8_t *data, size_t length) {
    uint32_t crc = 0xFFFFFFFFu;

    for (size_t i = 0; i < length; i++) {
        uint8_t index = (crc ^ data[i]) & 0xFF;
        crc = (crc >> 8) ^ crc32_table[index];
    }
    return crc ^ 0xFFFFFFFFu;
}

int main() {
    const char *input = "123456789";
    size_t len = strlen(input);

    init_crc32_table();

    printf("=== Day 27: CRC-32 Implementation ===\n");
    printf("Input Data: \"%s\"\n\n", input);

    uint32_t res_bit = crc32_bitwise((const uint8_t*)input, len);
    uint32_t res_table = crc32_table_based((const uint8_t*)input, len);

    printf("[Bit-wise] CRC: 0x%08X\n", res_bit);
    printf("[Table-based] CRC: 0x%08X\n\n", res_table);

    if (res_bit == res_table && res_bit == 0xCBF43926) {
        printf(">> Verification Success! (Matches Standard)\n");
    } else {
        printf(">> Verification Failed.\n");
    }

    return 0;
}