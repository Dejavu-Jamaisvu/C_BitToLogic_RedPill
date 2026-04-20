#include <stdio.h>
#include<time.h>

int sum(int a);

int main(void)
{

        int num;
        printf("함수의 재귀호출을 사용해서 1부터 n까지의 합을 계산?\n");
        scanf("%d", &num);
	int result;

        clock_t start = clock();
	
	result = sum(num);

        clock_t end = clock();
        double duration = (double)(end - start) / CLOCKS_PER_SEC;

	printf("\n1부터 %d까지 합은 %d 입니다.\n", num, result);
	printf("연산 소요 시간: %.4f초\n", duration);

}

int sum(int a)
{   
	if(a == 1)
		return 1;

	else
		return a + sum(a-1); 
}

