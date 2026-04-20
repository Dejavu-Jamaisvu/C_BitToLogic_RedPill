#include <stdio.h>
#include <stdlib.h>

int main() {
    int rows = 3, cols = 4;
    int count = 1;

    printf("=== Day 10: Dynamic 2D Array (Pointer Arithmetic) ===\n\n");

    //matrix:주소록(행 포인터 배열)의 시작주소, *matrix:주소록 첫 칸 값 = 주소록 행의 첫번째 열 시작주소, **matrix: 첫 칸이 가리키는 데이터 값
    int **matrix = (int **)malloc(rows * sizeof(int *));
    //data:실제 데이터 저장공간 시작주소, *data:첫 칸 안에 데이터 값
    int *data = (int *)malloc(rows * cols * sizeof(int));

    for (int i = 0; i < rows; i++) {
        *(matrix + i) = data + (i * cols); 
        //*matrix, data 같은 레벨
    }

    
    printf("Generated Matrix (%dx%d):\n", rows, cols);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
                
            *(*(matrix + i) + j) = count++;
            printf("%2d ", *(*(matrix + i) + j));
        }
        printf("\n");
    }

    free(data);
    free(matrix);

    printf("\n>> Memory successfully freed.\n");

    return 0;
}