#include <stdio.h>
#include <ctype.h>

typedef struct {
    unsigned int id;
    char name[12];
    float value;
} SensorData;

void hexdump(const char *title, void *addr, int len) {
    unsigned char *p = (unsigned char *)addr; 
    
    printf("%s:\n", title);

    for (int i = 0; i < len; i += 16) {

        // 주소 오프셋 
        printf("  %04x  ", i);

        // 16진수 데이터 16개
        for (int j = 0; j < 16; j++) {
            if (i + j < len) {
                printf("%02x ", p[i + j]);
            } else {
                printf("   "); // 데이터가 없는 빈 칸은 공백으로 채움
            }
        }

        printf(" ");

        // ASCII 표현
        for (int j = 0; j < 16; j++) {
            if (i + j < len) {
                unsigned char c = p[i + j];
                // 출력 가능한 ASCII (32(0x20) ~ 126(0x7E))
                if (c >= 32 && c <= 126) {
                    putchar(c);
                } else {
                    putchar('.'); // 출력 불가능하면 마침표 표시
                }
            }
        }
        printf("\n");
    }
    printf("\n");
}

int main() {
    // 테스트 1: 단순 문자열
    char my_text[] = "Hello Embedded World! This is Hexdump.";// 문자열 끝에 null 있음!
    hexdump("String Dump", my_text, sizeof(my_text));
  
    // 테스트 2: 구조체 (엔디안 확인 가능)
    SensorData sensor = { 0x12345678, "Sensor A", 3.14f };// 실수 3.14는 16진수로 c3 f5 48 40
    hexdump("Struct Dump", &sensor, sizeof(sensor));

    return 0;
}