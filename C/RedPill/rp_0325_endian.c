#include <stdio.h>
#include <stdint.h>

int main() {
    uint32_t data = 0x12345678; // Big Endian 가정 데이터
    uint32_t result = data;  //시스템이 빅 엔디안일 경우 대비 원본 저장  

    uint16_t check = 0x0001; //넣어볼 값 //16비트
    int is_little_endian = (*(uint8_t *)&check == 0x01); 
    //앞칸 8비트(1바이트) 상태확인 01 00이었다면 참. 00 01이었다면 거짓이 나옴.

    printf("=== Day 2: Endianness Conversion ===\n");
    printf("Received Data (Hex): 0x%08X\n\n", data);

    if (is_little_endian) {
        printf("[System Check] This system is Little Endian.\n");
        printf(" -> Need to swap bytes to match Host Order.\n\n");

	    // 0x12345678 -> 0x78563412
        result = ((data & 0x000000FF) << 24) |
                 ((data & 0x0000FF00) << 8)  |
                 ((data & 0x00FF0000) >> 8)  | 
                 ((data & 0xFF000000) >> 24); 
    } else {
        printf("[System Check] This system is Big Endian.\n");
        printf(" -> No swap needed.\n\n");
    }

    printf("Original (Network): 0x%08X\n", data);
    printf("Converted (Host)  : 0x%08X\n\n", result);

    uint8_t *p = (uint8_t *)&result; //result의 시작 주소 8비트씩
    printf("Memory Dump: ");
    for (int i = 0; i < 4; i++) {
        printf("[%02X] ", *p++); //*가 우선순위 높음 //printf("[%02X] ", p[i]); 
    }
    printf("(Low Addr -> High Addr)\n");
    //data 0x12345678 => 메모리 덤프 [78] [56] [34] [12]
    //result 0x78563412 => 메모리 덤프 [12] [34] [56] [78]
    //리틀엔디안인 컴퓨터는 LSB부터 거꾸로 읽기에 거꾸로 저장해줌 

    return 0;
}