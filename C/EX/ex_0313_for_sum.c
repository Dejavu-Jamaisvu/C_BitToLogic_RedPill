#include <stdio.h>
#include<time.h>

int sum(int a);
int sumfor(int a);

int main(void)
{

        int num;
        printf("재귀 및 for 사용해서 1부터 n까지의 합을 계산 - n입력 :\n");
        scanf("%d", &num);
        int result, result2;

        clock_t start = clock();

        result = sum(num);

        clock_t end = clock();
        double duration = (double)(end - start) / CLOCKS_PER_SEC;

        printf("\n1부터 %d까지 합은 %d 입니다.\n", num, result);
        printf("재귀 연산 소요 시간: %.10f초\n", duration);

        clock_t start2 = clock();

        result2 = sumfor(num);

        clock_t end2 = clock();
        double duration2 = (double)(end2 - start2) / CLOCKS_PER_SEC;


        printf("\n1부터 %d까지 합은 %d 입니다.\n", num, result2);
        printf("for 연산 소요 시간: %.10f초\n", duration2);

}

int sum(int a)
{
        if(a == 1)
                return 1;

        else
                return a + sum(a-1);
}

int sumfor(int a)
{
	int total=0;
        for(int i=0; i<=a;i++){
		total+=i;
	}
	return total;
}

