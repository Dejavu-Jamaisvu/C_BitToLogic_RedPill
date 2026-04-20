#include <stdio.h>
#include <stdarg.h>


void print_number(long long n, int base, int uppercase) {
    char buf[64];
    int i = 0;
    int is_negative = 0;

    if (n == 0) {
        putchar('0');
        return;
    }

    if (n < 0 && base == 10) {
        is_negative = 1;
        n = -n;
    }

    while (n > 0) {
        int rem = n % base;
        if (rem < 10) {
            buf[i++] = rem + '0';
        } else {
            buf[i++] = rem - 10 + (uppercase ? 'A' : 'a');
        }
        n /= base;
    }

    if (is_negative) putchar('-');
    

    while (i > 0) {
        putchar(buf[--i]);
    }
}


void my_printf(const char *format, ...) {
    va_list args; // 가변 인자 목록을 가리키는 포인터 변수 // 이동식 커서 역할
    va_start(args, format); // 가변 인자 시작점을 format 바로 다음 주소로 설정

    for (const char *p = format; *p != '\0'; p++) {
        if (*p == '%') {
            p++;
            switch (*p) {
                case 'd': { 
                    int val = va_arg(args, int);
                    print_number(val, 10, 0);
                    break;
                }
                case 'x': {
                    unsigned int val = va_arg(args, unsigned int);
                    print_number(val, 16, 1);
                    break;
                }
                case 's': {
                    char *val = va_arg(args, char *);

                    if (!val) val = ""; 
                    // 인자가 비어있는 주소가 와서 val의 값이 null일 때, val은 포인터이므로 ""이라는 문자열의 주소를 넣어줌.
                    // 없으면, NULL(0번지)에 가서 데이터 읽으려함 -> Segmentation Fault (프로그램 뻗음)

                    while (*val) putchar(*val++); 
                    break;
                }
                default: 
                    putchar('%');
                    putchar(*p);
                    break;
            }
        } else {
            putchar(*p);
        }
    }

    va_end(args); // 가변 인자 사용 해제. 포인터 무효화
}

int main() {
    printf("=== Day 28: Custom printf Implementation ===\n\n");

    // Test 1: 정수와 문자열
    my_printf("MyPrint: %d %s\n", 10, "test");

    // Test 2: 16진수와 음수
    my_printf("Hex: 0x%x, Negative: %d\n", 255, -12345);

    // Test 3: 여러 인자 혼합
    my_printf("Result: %d + %d = %d\n", 10, 20, 30);

    return 0;
}