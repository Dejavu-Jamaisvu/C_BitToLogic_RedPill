#include <stdio.h>

int main(void)
{
    int id;
    int temp;
    int humi;
    char packet[255];
    
    printf("문자열 패킷을 입력해 주세요.\nID:[숫자];TEMP:[숫자];HUMI:[숫자]\n");
    scanf("%s", packet);

    sscanf(packet, "%*[^:]%*[:]%d%*[^:]%*[:]%d%*[^:]%*[:]%d", &id, &temp, &humi);

    printf("=== Sensor Data Report ===\n");
    printf("Device ID  : %d\n", id);
    printf("Temperature: %d C \n", temp);
    printf("Humidity   : %d %%\n", humi);
    printf("==========================\n");

    return 0;
}

