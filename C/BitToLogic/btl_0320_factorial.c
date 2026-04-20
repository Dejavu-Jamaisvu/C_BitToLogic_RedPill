#include <stdio.h>

// int MAX_LIMIT = 2; 
int MAX_LIMIT = 10; 

int factorial(int n, int depth) {
    int local_var = n; 
    
    printf("Depth %d: Addr of n = %p, Value = %d\n", depth, (void*)&n, n);
    
    if (depth > MAX_LIMIT) {
        printf("Stack Limit Exceeded!\n");
        return -1; 
    }

    if (n <= 1) 
        return 1;

    int result = factorial(n - 1, depth + 1);
    
    if (result == -1) 
        return -1;

    return n * result;
}

int main() {
    int n = 5;

    printf("--- Stack Trace Start ---\n");

    int final_res = factorial(n, 1);
    
    if (final_res != -1) {
        printf("Result: %d\n", final_res);
    }

    return 0;
}