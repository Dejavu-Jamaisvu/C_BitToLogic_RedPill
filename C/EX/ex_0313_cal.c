#include <stdio.h>

int main(void)
{
    int n1, n2, result;
    char op;


    printf("사칙연산 입력(정수) ex)11/3 : ");
   

    scanf("%d%c%d", &n1, &op, &n2);

    switch (op) 
    {
    case '+': 
	result = n1+n2;	
	break;
    case '-':     
	result = n1-n2;	
        break;  
    case '*':     
	result = n1*n2;	
        break;
    case '/':
	result = n1/n2;
	break;	
    default:   
        printf("예시와 같이 사칙연산을 입력하세요\n");
        return 0;
    }

    printf("result : %d\n", result);

    return 0;
}
