#include <stdio.h>
#include <stddef.h> 

/*
 * [핵심 매크로] my_offsetof
 * type: 구조체 타입 이름 (예: struct Data)
 * member: 멤버 변수 이름 (예: b)
 */
#define my_offsetof(type, member)  ((size_t)&(((type *)0)->member))

// 테스트를 위한 구조체 (패딩이 발생하는 구조)
//#pragma pack(1) 
typedef struct {
    char a;      // 1 byte
    // (padding 3 bytes) - 4바이트 정렬을 위해 컴파일러가 넣음
    int b;       // 4 bytes
    double c;    // 8 bytes
} Sample;

int main() {
    printf("=== Day 12: offsetof Implementation ===\n\n");

    printf("Struct Size: %zu bytes\n\n", sizeof(Sample));

    printf("[Standard] Offset of a: %zu\n", offsetof(Sample, a));
    printf("[Standard] Offset of b: %zu\n", offsetof(Sample, b));
    printf("[Standard] Offset of c: %zu\n", offsetof(Sample, c));

    printf("\n-----------------------------\n\n");
    size_t off_a = my_offsetof(Sample, a);
    size_t off_b = my_offsetof(Sample, b);
    size_t off_c = my_offsetof(Sample, c);

    printf("[My Macro] Offset of a: %zu\n", off_a);
    printf("[My Macro] Offset of b: %zu\n", off_b);
    printf("[My Macro] Offset of c: %zu\n", off_c);

    if (off_a == offsetof(Sample, a) && 
        off_b == offsetof(Sample, b) && 
        off_c == offsetof(Sample, c)) {
        printf("\n>> Success! Implementation is correct.\n");
    } else {
        printf("\n>> Failure! Implementation is incorrect.\n");
    }

    return 0;
}