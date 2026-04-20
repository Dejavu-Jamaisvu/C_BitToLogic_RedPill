#include <stdio.h>

#define IS_VALID_POS(pos) ((pos) >= 0 && (pos) <= 31)


unsigned int set_bit(unsigned int reg, int pos) {
    return reg | (1U << pos);
}

unsigned int clear_bit(unsigned int reg, int pos) {
    return reg & ~(1U << pos);
}

unsigned int toggle_bit(unsigned int reg, int pos) {
    return reg ^ (1U << pos);
}

int check_bit(unsigned int reg, int pos) {
    return (reg >> pos) & 1U;
}

void print_binary(unsigned int n) {
    for (int i = 31; i >= 0; i--) {
        printf("%d", (n >> i) & 1);
        if (i % 8 == 0 && i != 0) printf(" ");
    }
}

int main() {
    unsigned int reg, result;
    int pos, menu, status = -1;

    printf("초기 16진수 입력 (ex: 0000FFFF): 0x");
    scanf("%x", &reg);

    printf("\n--- BIT COMMAND MENU ---\n");
    printf("1. SET    2. CLEAR    3. TOGGLE    4. CHECK\n");
    printf("명령 번호를 선택하세요: ");
    scanf("%d", &menu);

    printf("조작할 비트 위치(0~31) 입력: ");
    scanf("%d", &pos);

    if (!IS_VALID_POS(pos) || menu < 1 || menu > 4) {
        printf("\n[오류] 잘못된 입력입니다. 위치는 0~31, 메뉴는 1~4여야 합니다.\n");
        return 1;
    }

    printf("\n[ORIGIN]: 0x%08X (", reg);
    print_binary(reg);
    printf(")\n");


    result = reg; 
    switch (menu) {
        case 1: result = set_bit(reg, pos);    break;
        case 2: result = clear_bit(reg, pos);  break;
        case 3: result = toggle_bit(reg, pos); break;
        case 4: status = check_bit(reg, pos);  break;
    }

    if (menu == 4) {
        // 4번 비트 상태 출력
        printf("[CHECK]: %d번 비트의 상태는 [%d] 입니다.\n", pos, status);
    } else {
        // 1~3번 비트연산 결과 출력
        printf("[RESULT]: 0x%08X (", result);
        print_binary(result);
        printf(")\n");
    }

    return 0;
}