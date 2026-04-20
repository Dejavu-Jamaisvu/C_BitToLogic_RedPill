#include <stdio.h>

/*

1바이트(char): 아무 주소에나 올 수 있음.
2바이트(short): 2의 배수 주소에 와야 함.
4바이트(int): 4의 배수 주소에 와야 함.
*/

struct NormalPacket {
    unsigned char id;        // 1  
    // [ 여기에 3바이트 패딩이 삽입됨 ]
    unsigned int timestamp;  // 4
    unsigned short data;     // 2 
    unsigned char checksum;  // 1  
    // [ 구조체 전체 크기를 4의 배수로 맞추기 위해 1바이트 패딩 추가 ]
};

// 패딩을 제거 설정 (1바이트 단위 정렬)
#pragma pack(push, 1)
struct PackedPacket {
    unsigned char id;        // 1
    unsigned int timestamp;  // 4
    unsigned short data;     // 2
    unsigned char checksum;  // 1
};
#pragma pack(pop)

int main() {
    struct NormalPacket n_pkt;
    struct PackedPacket p_pkt;

    printf("Normal Struct Size: %zu bytes\n", sizeof(struct NormalPacket));
    printf("Packed Struct Size: %zu bytes\n\n", sizeof(struct PackedPacket));

    printf("[ NormalPacket - Member Addresses]\n");
    printf("id (char)      : %p\n", (void*)&n_pkt.id);
    printf("timestamp (int): %p\n", (void*)&n_pkt.timestamp);
    printf("data (short)   : %p\n", (void*)&n_pkt.data);
    printf("checksum (char): %p\n", (void*)&n_pkt.checksum);
    
    unsigned long n_gap1 = (unsigned long)&n_pkt.timestamp - (unsigned long)&n_pkt.id;
    unsigned long n_gap2 = (unsigned long)&n_pkt.data - (unsigned long)&n_pkt.timestamp;
    unsigned long n_gap3 = (unsigned long)&n_pkt.checksum - (unsigned long)&n_pkt.data;

    printf("\n");
    printf(">> id와 timestamp 사이 간격: %lu bytes %s\n", n_gap1, (n_gap1 > 1) ? "(Padding)" : "");
    printf(">> timestamp와 data 사이 간격: %lu bytes %s\n", n_gap2, (n_gap2 > 4) ? "(Padding)" : "");
    printf(">> data와 checksum 사이 간격: %lu bytes %s\n\n", n_gap3, (n_gap3 > 2) ? "(Padding)" : "");

    printf("-------------------------------------------\n\n");

    printf("[ PackedPacket - Member Addresses]\n");
    printf("id (char)      : %p\n", (void*)&p_pkt.id);
    printf("timestamp (int): %p\n", (void*)&p_pkt.timestamp);
    printf("data (short)   : %p\n", (void*)&p_pkt.data);
    printf("checksum (char): %p\n", (void*)&p_pkt.checksum);

    unsigned long p_gap1 = (unsigned long)&p_pkt.timestamp - (unsigned long)&p_pkt.id;
    unsigned long p_gap2 = (unsigned long)&p_pkt.data - (unsigned long)&p_pkt.timestamp;
    unsigned long p_gap3 = (unsigned long)&p_pkt.checksum - (unsigned long)&p_pkt.data;
    
    printf("\n");
    printf(">> id와 timestamp 사이 간격: %lu bytes %s\n", p_gap1, (p_gap1 > 1) ? "(Padding)" : "");
    printf(">> timestamp와 data 사이 간격: %lu bytes %s\n", p_gap2, (p_gap2 > 4) ? "(Padding)" : "");
    printf(">> data와 checksum 사이 간격: %lu bytes %s\n", p_gap3, (p_gap3 > 2) ? "(Padding)" : "");

    return 0;
}