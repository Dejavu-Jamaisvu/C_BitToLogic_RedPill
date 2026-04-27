#include <stdio.h>

const char* myStrtok(const char* str, const char* delim, int* out_len) {

    static const char* next_ptr = NULL;

    // 첫 호출 시 시작 주소 설정
    if (str != NULL) next_ptr = str;
    
    // 읽을 주소가 없거나 이미 끝문자('\0')라면 종료
    if (next_ptr == NULL || *next_ptr == '\0') return NULL;

    // 연속으로 들어오는 구분자 건너뛰기
    while (*next_ptr != '\0' && *next_ptr == delim[0]) {
        next_ptr++;
    }

    // 구분자만 나오다가 문자열이 끝난 경우 처리
    if (*next_ptr == '\0') return NULL;

    const char* start = next_ptr;
    while (*next_ptr != '\0' && *next_ptr != delim[0]) {
        next_ptr++;
    }

    *out_len = (int)(next_ptr - start);

    // 현재 위치가 구분자라면, 다음 호출을 위해 한 칸 건너뜀
    if (*next_ptr != '\0') {
        next_ptr++;
    }

    return start; 
}

int main() {
    const char* input = "GPS,37.5665,126.9780,20260213";
    const char* delim = ",";
    int len = 0;

    printf("=== Day 23: Safe String Tokenizer (Single Delim) ===\n\n");
    printf("Input Data: \"%s\"\n", input);
    printf("Delimiter : '%s'\n\n", delim);

    int count = 1;
    const char* token = myStrtok(input, delim, &len);
    while (token != NULL) {
        printf("Token %d: %.*s\n", count++, len, token);
        // printf("%.*s", 길이, 주소);
        // 인자로 받은 길이만큼만 주소에서 읽어서 출력
        token = myStrtok(NULL, delim, &len);
    }

    printf("\n>> Original string check: \"%s\"\n", input);
    
    const char* expected = "GPS,37.5665,126.9780,20260213";
    int is_modified = 0;
    
    for (int i = 0; input[i] != '\0' || expected[i] != '\0'; i++) {
        if (input[i] != expected[i]) {
            is_modified = 1;
            break;
        }
    }

    if (!is_modified) {
        printf(">> (Original string remains unmodified)\n");
    } else {
        printf(">> (Warning: Original string was modified!)\n");
    }

    return 0;
}