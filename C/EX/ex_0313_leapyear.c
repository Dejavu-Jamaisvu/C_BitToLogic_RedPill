#include <stdio.h>

int main(void)
{
    int leap_year;


    printf("연도를 입력하세요\n");
    scanf("%d", &leap_year);

    if(leap_year % 4 ==0)
	    if(leap_year % 100 == 0)
    		    if(leap_year % 400==0)
			    printf("윤년입니다.\n");
    		    else 
			    printf("윤년이 아닙니다.\n");
	    else
    		    printf("윤년입니다.\n");
    else
    	    
    	printf("윤년이 아닙니다.\n");
    return 0;
}
