#include <stdio.h>

int main() {
    int input[5][5];
    int kernel[3][3];
    int output[3][3];
    char c; // 행구분 슬래시 담는용

    printf("input 5X5 데이터를 입력하세요\n");
    printf("ex) 1 2 3 0 1 / 0 1 2 3 0 / 1 0 1 2 3 / 3 2 1 0 1 / 0 1 2 3 0 \n");
    for(int i=0; i<5; i++){
        for(int j=0; j<5; j++){
            scanf("%d", &input[i][j]);
        }
        if(i < 4) 
		scanf(" %c", &c);
    }

    printf("kernel 3X3 데이터를 입력하세요\n");
    printf("ex) 1 0 1 / 0 1 0 / 1 0 1 \n");
    for(int i=0; i<3; i++){
        for(int j=0; j<3; j++){
            scanf("%d", &kernel[i][j]);
        }
        if(i < 2) 
		scanf(" %c", &c);
    }

    for(int i=0; i<3; i++){
        for(int j=0; j<3; j++){
            int sum = 0;
            for(int m=0; m<3; m++){
                for(int n=0; n<3; n++){
                    sum += input[i+m][j+n] * kernel[m][n];
                }
            }
            output[i][j] = sum;
        }
    }

    printf("\noutput 3X3 데이터\n");
    for(int i=0; i<3; i++){
        for(int j=0; j<3; j++){
            printf("%d ", output[i][j]);
        }
        printf("\n");
    }

    return 0;
}
