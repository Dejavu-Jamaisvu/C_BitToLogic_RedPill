#include <stdio.h>
#include <stdlib.h> // malloc, free
#include <limits.h> //INT_MIN

int main() {
    int n;
    int *ptr = NULL;
    int max = INT_MIN;
    double sum = 0;

    printf("수집할 센서 데이터의 개수를 입력하세요. -> ");

    // scanf("%d", &n);
    if ( scanf("%d", &n) != 1 || n < 0) { 
        // scanf("%d", &n) == 1 
        // 성공적으로 입력받은 변수 개수 1
        // -> 숫자 형식인지 확인. 음수 제외.

        printf("[Error] 숫자를 입력하세요.\n\n");
        return 1;
    }

    if (n == 0) { // 0일때는 할당하지 않고 바로 NULL 대입해서 예외처리 체크 가능
        ptr = NULL;
        printf("[info] 데이터 개수가 0일 때는 ptr = NULL !!\n");
    } else {
        ptr = (int *)malloc(n * sizeof(int));
    }

    if (ptr == NULL) {
        if (n == 0) {
            printf("[Error] 메모리를 할당할 수 없습니다. 데이터 개수를 1이상 넣어주세요.\n");
        } else {
            printf("[Error] 메모리 부족으로 할당 실패!\n");
        }
        return 1;
    }
    printf("Allocated at: %p\n", (void *)ptr);

    printf("\n정수 데이터를 %d개 입력하세요 -> ", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", (ptr + i));
        
        if (*(ptr + i) > max) {
            max = *(ptr + i);
        }

        sum += *(ptr + i);
    }

    printf("\nAverage: %.2f, ", sum / n);
    printf("Max: %d\n", max);

    printf("\n메모리 해제 전 주소값 = %p\n", (void *)ptr);

    free(ptr);
    ptr = NULL;   // 댕글링 포인터(Dangling Pointer) 방지
    // free해도 ptr에 주소값은 그대로 들어있음.
    // 이후 *ptr = 10;이라고 코드를 짜면, 이미 반납한 주소에 값을 쓰려고 함.
    // => free는 메모리 비우기, ptr = NULL은 포인터 변수(이름표) 지우기.

    printf("Memory freed successfully\n");

    return 0;
}