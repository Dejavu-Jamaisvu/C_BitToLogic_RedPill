#include <stdio.h>
#include <stdint.h>
#include <string.h>

void* my_memmove(const void* src, void* dest, size_t n) {
    uint8_t* d = (uint8_t*)dest;
    const uint8_t* s = (const uint8_t*)src;

    if (d == s || n == 0) return dest;

    if (d > s && d < s + n) { // 뒤에서부터 복사 (Backward)
        // 포인터를 데이터의 끝 지점으로 이동
        d += n; 
        s += n;
        while (n--) {
            *(--d) = *(--s);
        }
    } else { // 앞에서부터 복사 (Forward)
        while (n--) {
            *(d++) = *(s++);
        }
    }
    return dest;
}

void dump(const char* label, uint8_t* data, size_t size) {
    printf("%-10s: ", label);
    for (size_t i = 0; i < size; i++) {
        printf("%02X ", data[i]);
    }
    printf("\n");
}

int main() {
    // 목적지가 뒤에 있는 경우 (뒤에서부터 복사 필요)
    uint8_t buffer1[10] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00};
    printf("--- Forward Overlap (dest > src) ---\n");
    dump("Before", buffer1, 10);
    my_memmove(&buffer1[0], &buffer1[2], 5); 
    dump("After", buffer1, 10);
    printf("\n");

    // 목적지가 앞에 있는 경우 (앞에서부터 복사 필요)
    uint8_t buffer2[10] = {0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x00};
    printf("--- Backward Overlap (dest < src) ---\n");
    dump("Before", buffer2, 10);
    my_memmove(&buffer2[4], &buffer2[0], 5); 
    dump("After", buffer2, 10);

    return 0;
}