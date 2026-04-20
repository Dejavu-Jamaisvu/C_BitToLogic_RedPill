#include <stdio.h>

void parseRGB565(unsigned short input) {

    unsigned char r_raw = (input & 0xF800) >> 11;
    unsigned char g_raw = (input & 0x07E0) >> 5;
    unsigned char b_raw = (input & 0x001F);

    // 8비트 확장
    unsigned char r_ext = r_raw << 3;
    unsigned char g_ext = g_raw << 2;
    unsigned char b_ext = b_raw << 3;

    printf("Input: 0x%04X\n", input);
    printf("  [Raw Value] R: %2d (0x%02X), G: %2d (0x%02X), B: %2d (0x%02X)\n", 
            r_raw, r_raw, g_raw, g_raw, b_raw, b_raw);
    printf("  [8-bit Ext] R: %3d,      G: %3d,      B: %3d\n", 
            r_ext, g_ext, b_ext);
    printf("--------------------------------------------------\n");
}

int main() {
    printf("=== Day 3: Packed Data Parsing (RGB565) ===\n\n");
    parseRGB565(0xFFFF);
    parseRGB565(0xF800);
    parseRGB565(0x07E0);
    parseRGB565(0x1234);
    return 0;
}