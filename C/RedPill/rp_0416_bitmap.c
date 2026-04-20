#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>


typedef struct {
    uint8_t *map;   // 실제 비트들을 담을 바이트 배열
    int total_bits; // 관리할 리소스 총 개수
    int array_size; // 배열의 크기 (바이트 단위)
} Bitmap;


Bitmap* create_bitmap(int total_bits) {
    Bitmap *bmp = (Bitmap*)malloc(sizeof(Bitmap));
    bmp->total_bits = total_bits;
    bmp->array_size = (total_bits + 7) / 8; // 바이트로 몇개인지
    bmp->map = (uint8_t*)calloc(bmp->array_size, sizeof(uint8_t)); // 0으로 초기화 // 몇개, 개당크기
    return bmp;
}

int allocate_resource(Bitmap *bmp) {
    for (int i = 0; i < bmp->total_bits; i++) {
        int byte_idx = i / 8;
        int bit_idx = i % 8;

        if (!(bmp->map[byte_idx] & (1 << bit_idx))) { // 비어있는(0인) 비트
            bmp->map[byte_idx] |= (1 << bit_idx); 
            printf(">> Index %d allocated. (Byte %d, Bit %d set)\n", i, byte_idx, bit_idx);
            return i;
        }
    }
    return -1; // 할당 실패 (가득 참)
}

void free_resource(Bitmap *bmp, int index) {
    if (index < 0 || index >= bmp->total_bits) return;

    int byte_idx = index / 8;
    int bit_idx = index % 8;

    bmp->map[byte_idx] &= ~(1 << bit_idx);
    printf(">> Index %d freed. (Byte %d, Bit %d cleared)\n", index, byte_idx, bit_idx);
}


void print_bitmap_visual(Bitmap *bmp) {
    printf("[Bitmap Visual] ");
    for (int i = 0; i < bmp->array_size; i++) {
        for (int j = 0; j < 8; j++) {
            if ((i * 8 + j) < bmp->total_bits) {
                int bit = (bmp->map[i] >> j) & 1;
                printf("%d", bit);
            }
        }
        if (i < bmp->array_size - 1) printf(" | ");
    }
    printf("\n");
}


int main() {
    printf("=== Day 17: Bitmap Manager ===\n\n");

    // 1. 20개의 리소스를 관리하는 비트맵 생성 (3바이트 필요)
    Bitmap *bmp = create_bitmap(20);

    // 2. 할당 테스트
    allocate_resource(bmp); // idx 0
    allocate_resource(bmp); // idx 1
    int id7 = allocate_resource(bmp); // idx 2 ... (반복해서 7까지 채움)
    for(int i=0; i<5; i++) allocate_resource(bmp); 
    
    print_bitmap_visual(bmp);

    // 3. 해제 테스트
    printf("\nFreeing index 2...\n");
    free_resource(bmp, 2);
    
    print_bitmap_visual(bmp);

    // 4. 재할당 (빈 공간인 2번이 다시 할당되어야 함)
    printf("\nAllocating again (expecting index 2)...\n");
    allocate_resource(bmp);

    print_bitmap_visual(bmp);

    // 정리
    free(bmp->map);
    free(bmp);

    return 0;
}