
#include<stdio.h>
#include<time.h>

int main(){

	int num;
	printf("소수구하기. 어디까지 구할까요?\n");
	scanf("%d", &num);

	clock_t start = clock();
	int pNum=0;
	for(int i=2;i<=num;i++){
	        int count=0;
	        for(int j=1;j<i;j++){
		
			if(i%j ==0){
				count++;
			}
	    	}
		if(count==1){
			pNum++;
			if(pNum%5==0)
                        	printf("%d\n",i);
                        else
                                printf("%d\t",i);
	        }
	}

	clock_t end = clock();
	double duration = (double)(end - start) / CLOCKS_PER_SEC;

        printf("\n2부터 %d까지 소수는 총 %d개 입니다.\n", num, pNum);
        printf("연산 소요 시간: %.4f초\n", duration);

}
