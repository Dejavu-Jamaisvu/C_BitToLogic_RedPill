#include <stdio.h>

#define ROWS 10
#define COLS 10

typedef struct {
    int row;
    int col;
    int val;
} Element;

int main() {
    int matrix[ROWS][COLS] = {0}; 

    matrix[0][1] = 5;
    matrix[2][3] = 8;
    matrix[4][0] = 2;
    matrix[4][5] = 9;

    Element compressed[ROWS * COLS]; 
    int count = 0;

    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            if (matrix[i][j] != 0) {
                compressed[count].row = i;
                compressed[count].col = j;
                compressed[count].val = matrix[i][j];
                count++;
            }
        }
    }

    printf("=== Day 20: Sparse Matrix Compression ===\n\n");

    printf("--- Compressed Data (Row, Col, Val) ---\n");
    for (int i = 0; i < count; i++) {
        printf("Index %d: (%d, %d, %d)\n", i, compressed[i].row, compressed[i].col, compressed[i].val);
    }

    int total_elements = ROWS * COLS;
    int originalSize = total_elements * sizeof(int);
    int compressedSize = count * sizeof(Element);
    float ratio = ((float)compressedSize / originalSize) * 100;

    printf("\n[Memory Usage Analysis]\n");
    printf("Original Matrix Size : %d bytes (%d x 4 ints)\n", originalSize, total_elements);
    printf("Compressed Data Size : %d bytes (%d elements x3 x 4 bytes)\n", compressedSize, count);
    printf(">> Compression Ratio : %.1f%% of original size\n", ratio);

    return 0;
}