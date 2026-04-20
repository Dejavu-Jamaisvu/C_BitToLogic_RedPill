#include <stdio.h>

int main(void)
{
    char s[255];
    int count = 0;
    int i = 0;

    printf("문장 입력 : ");
    fgets(s, sizeof(s), stdin);

    while (s[i] != '\0')
    {
        if (s[i] >= 65 && s[i] <= 90)
        {
            s[i] += 32;
            count++;
        }
        i++;
    }

    printf("바뀐 문장 : %s", s);
    printf("바뀐 문자 수 : %d\n", count);

    return 0;
}
