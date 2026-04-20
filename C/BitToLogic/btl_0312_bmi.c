#include <stdio.h>

int main(void)
{
    double kg;
    double cm;

    printf("몸무게와 키를 입력해주세요.\n");
    scanf("%lf", &kg);
    scanf("%lf", &cm);
    
    double m = cm*0.01;
    double bmi = kg/(m*m);

    if(bmi >=20.0 && bmi <25.0)
	    printf("%.2lf 표준입니다.\n", bmi);
    else
	    printf("%.2lf 체중관리가 필요합니다\n", bmi);

    return 0;
}

