#include <stdio.h>
#include <stddef.h> // ptrdiff_t를 쓰기 위한 헤더

int main() {
    int src[5] = {1, 2, 3, 4, 5};
    int dst[5] = {10, 20, 30, 40, 50};
    int size = sizeof(src) / sizeof(src[0]); // 5

    int *p_src = src;
    int *p_dst = dst;

    printf("[Before Swap]\n");
    printf("src: ");
    for (int i = 0; i < size; i++) printf("%d ", *(p_src + i));
    printf("\ndst: ");
    for (int i = 0; i < size; i++) printf("%d ", *(p_dst + i));
    printf("\n\n");

    for (int i = 0; i < size; i++) {
        int temp = *(p_src + i); 
        *(p_src + i) = *(p_dst + i); 
        *(p_dst + i) = temp; 
    }

 
    printf("[After Swap]\n");
    printf("src: ");
    for (int i = 0; i < size; i++) printf("%d ", *(p_src + i));
    printf("\ndst: ");
    for (int i = 0; i < size; i++) printf("%d ", *(p_dst + i));
    printf("\n\n");


    int *start_ptr = src; 
    int *end_ptr = src + (size - 1); 

    //64비트 환경에서는 주소값이 커서 long이나 long long에 담음
    //long distance = (char *)end_ptr - (char *)start_ptr; //char *으로 1바이트 단위로 변환
    
    //ptrdiff_t사용하면, 자동으로 시스템에 맞춰 long이나 long long 사용됨
    ptrdiff_t distance = (char *)end_ptr - (char *)start_ptr;

    printf("[Memory Info - src array]\n");
    printf("Start Address: %p\n", (void *)start_ptr); //(void *): 크기 정보 없음
    printf("End Address:   %p\n", (void *)end_ptr);
    printf("Distance:      %td bytes\n", distance);
    // %td(ptrdiff_t 전용), %lld (long long용), %ld (long용)

    return 0;
}