#include <stdio.h>
#include <stdint.h>

// [TX] 체크섬 계산: 첫 바이트, 마지막 바이트 제외
uint8_t calculate_xor_tx(const uint8_t *ptr, size_t len) {
    if (len <= 2) return 0;

    uint8_t crc = 0;
    const uint8_t *p = ptr + 1;          // 첫 바이트 제외
    const uint8_t *end = ptr + len - 1;  // 마지막 바이트 제외

    while (p < end) {
        crc ^= *p++; // ++이 우선이지만, 후위라서 * 먼저함

    }
    return crc;
}

// [RX] 검증용 XOR: 첫 바이트, 마지막에서 두번째 바이트 제외, 마지막 체크섬 포함
uint8_t calculate_xor_rx(const uint8_t *ptr, size_t len) {
    if (len <= 2) return 0;

    uint8_t crc = 0;
    const uint8_t *p = ptr + 1;          // 첫 바이트 제외
    const uint8_t *end = ptr + len - 2;  // 마지막 2개 제외 (0x40 + checksum)

    while (p < end) {
        crc ^= *p++;
    }

    // 마지막에 checksum까지 XOR
    crc ^= *(ptr + len - 1);

    return crc;
}

// 송신부
void process_tx_packet(const uint8_t *data, size_t len) {
    uint8_t checksum = calculate_xor_tx(data, len);

    printf("[TX] Sending Packet...\n");
    printf("     Data: ");
    for (size_t i = 0; i < len; i++) printf("0x%02X ", data[i]);
    printf("\n     Calculated Checksum: 0x%02X\n\n", checksum);
}

// 수신부
void process_rx_packet(const char *msg, const uint8_t *packet, size_t len) {
    uint8_t result = calculate_xor_rx(packet, len);

    printf("%s\n", msg);

    if (result == 0) {
        printf("     >> Verification SUCCESS (Result: 0x00)\n\n");
    } else {
        printf("     Corrupted Data: ");
        for (size_t i = 0; i < len; i++) printf("0x%02X ", packet[i]);
        printf("\n     >> Verification FAIL (Result: 0x%02X)\n", result);
        printf("     >> Error detected! Discarding packet.\n\n");
    }
}

int main() {
    printf("=== Day 7: XOR Checksum Calculation ===\n\n");

    uint8_t tx_raw[] = {0x01, 0x04, 0x10, 0x20, 0x30, 0x40};
    process_tx_packet(tx_raw, 6);

    uint8_t rx_normal[] = {0x01, 0x04, 0x10, 0x20, 0x30, 0x40, 0x04};
    process_rx_packet("[RX] Receiving Normal Packet...", rx_normal, 7);

    uint8_t rx_corrupted[] = {0x01, 0x04, 0xEF, 0x20, 0x30, 0x40, 0x04};
    process_rx_packet("[RX] Receiving Corrupted Packet (Noise injected)...", rx_corrupted, 7);

    return 0;
}