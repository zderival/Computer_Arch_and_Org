#include <stdio.h>
unsigned int SetBit(unsigned int value, int position) {
    if (position < 0 || position >= 32) {
        return value;
    }
    return value | (1 << position);
}
unsigned int ClearBit(unsigned int value, int position) {
    if (position < 0 || position >= 32) return value;
    return value & ~(1u << position);
}
unsigned int FlipBit(unsigned int value, int position) {
    if (position < 0 || position >= 32) return value;
    unsigned int flip = (1u << position);
    return value ^ flip;
}

int BitVal(unsigned int value, int position) {
    if (position < 0 || position >= 32) return 0;
    return (value >> position) & 1u;
}

int CountBits(unsigned int value ) {
    int count = 0;
    while (value != 0) {
        count += value & 1;
        value >>= 1;
    }
    return count;
}
unsigned int ShiftLeft ( unsigned int value, int positions ) {
    if (positions < 0 || positions >= 32) return value;
    return (value << positions);
}
unsigned int ShiftRight (unsigned int value, int positions ) {
    if (positions < 0 || positions >= 32) return value;
    return (value >> positions);
}

void PrintBinary(unsigned int value) {
    for (int i = 31; i >= 0; i--) {
        unsigned int bit = (value >> i) & 1;
        printf("%u", bit);
        if (i % 4 == 0) {
            printf(" ");
        }
    }
}
void PrintHex(unsigned int value) {
    printf("0x%08X\n", value);
}