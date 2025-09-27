#include <stdio.h>
#include <string.h>
#include <stdint.h>

void div_convert(uint32_t n, int base, char *out){
    if(n == 0) {
        out[0] = '0';
        out[1] = '\0';
        return;
    }
    int i = 0;
    while (n > 0) {
        int remainder = n % base;
        if (remainder < 10) {
            out[i++] = '0' + remainder;
        }else {
            out[i++] = 'A' + (remainder - 10);
        }
        n /= base;
    }
    out[i] = '\0';
    for (int j = 0; j < i /2; j++) {
        char temp = out[j];
        out[j] = out[i - 1 - j];
        out[i - 1 - j] = temp;
    }
}
void sub_convert(uint32_t n, int base, char *out) {
    if (n == 0) {
        out[0] = '0';
        out[1] = '\0';
        return;
    }

    int i = 0;
    uint32_t power = 1;

    while(power <= n / base) {
        power *= base;
    }
    while (power > 0) {
        int digit = n / power;
        n -= digit * power;

        if (digit < 10) {
            out[i++] = '0' + digit;
        }else {
            out[i++] = 'A' + (digit - 10);
        }
        power /= base;
    }
    out[i] = '\0';
}
void print_tables(uint32_t n) {
    char bin[33], oct[12], hex[9];
    div_convert (n , 2 , bin ) ;
    div_convert (n , 8 , oct ) ;
    div_convert (n , 16 , hex ) ;
    printf("Original: Binary=%s Octal=%s Decimal=%u Hex=%s\n",
    bin , oct , n , hex );

    uint32_t shifted = n << 3;
    div_convert ( shifted , 2 , bin ) ;
    div_convert ( shifted , 8 , oct ) ;
    div_convert ( shifted , 16 , hex ) ;
    printf ("Left Shift by 3: Binary=%s Octal=%s Decimal=%u Hex=%s\n",
    bin , oct , shifted , hex );

    uint32_t masked = n & 0xFF;
    div_convert( masked , 2, bin ) ;
    div_convert( masked , 8, oct ) ;
    div_convert( masked , 16, hex );
    printf("AND with 0xFF: Binary=%s Octal=%s Decimal=%u Hex=%s\n",
        bin, oct, masked, hex);
}

void oct_to_bin(const char *oct, char *out) {
    int j = 0;
    for (int i=0; oct[i] != '\0'; i++) {
        int digit = oct[i] - '0';
        out[j++] = (digit >> 2) & 1 ? '1':'0';
        out[j++] = (digit >> 1) & 1 ? '1':'0';
        out[j++] = (digit >> 0) & 1 ? '1':'0';
    }
    out[j] = '\0';
}
void oct_to_hex(const char *oct, char *out) {
    char bin[128];
    oct_to_bin(oct,bin); // Turning oct's into binary numbers

    int len = strlen(bin); // getting the length of the buffer
    int padding = (4 - (len % 4)) % 4; // (len % 4) is checking how many bits are left hanging after checking a group of 4 bits.
    //If there is bits remaining (4 - the remainder) checks how many 0's you need to pad to fill in the hexadecimal
    // The last % 4 is just checking for security to see if you have it all.
    // In general, padding is holding the 0's you need to pad your binary number with

    char padded[128]; // padded is holding the padded binary digits that were made with padding.
    // These will be used to make the hexadecimals

    // This loop is doing the padding:
    for (int i = 0; i < padding; i++) {
        padded[i] = '0';
    }
    strcpy(padded + padding, bin); // padded is filled with 0's bin (binary num) is getting added into padded

    int j = 0; // Tracker for where you are in out buffer
    // The loop is taking 4 bits at a time
    for (int i = 0; i < strlen(padded); i += 4) {
        // val, is converting the bit to a number, then shifting that number 2^3,2^2,2^1,or 2^0 times
        // shifting is: x << n == x * 2^n
        int val = (padded[i] - '0') << 3 |
                  (padded[i+1] - '0') << 2 |
                  (padded[i+2] - '0') << 1 |
                  (padded[i+3] - '0');
        // converting the val to a hex character
        // if the value is 0-9 then the hex is 0-9
        if (val < 10)
            out[j++] = val + '0';
        // else if the value is 10 or more: the hex letters are A–F
        else
            out[j++] = (val - 10) + 'A';
    }
    // closes the buffer after everything is done
    out[j] = '\0';

}
void hex_to_bin(const char *hex, char *out) {
    int j = 0;
    for (int i = 0; hex[i] != '\0'; i++ ) {
        int val = 0;
        if ('0' <= hex[i] && hex[i] <= '9') {
            val = hex[i] - '0';
        }else if ('A' <= hex[i] && hex[i] <= 'F') {
            val = hex[i] - 'A' + 10;
        }else if ('a' <= hex[i] && hex[i] <= 'f') {
            val = hex[i] - 'a' + 10;
        }
        out[j++] = (val >> 3) & 1 ? '1':'0';
        out[j++] = (val >> 2) & 1 ? '1':'0';
        out[j++] = (val >> 1) & 1 ? '1':'0';
        out[j++] = (val >> 0) & 1 ? '1':'0';
    }
    out[j] = '\0';
}

void to_sign_magnitude(int32_t n, char *out) {
    uint32_t magnitude;

    if (n >= 0) {
        magnitude = (int32_t)n;
        out[0] = '0';
    }else {
        magnitude = (int32_t)(-n);
        out[0] = '1';
    }

    for (int i = 31; i > 0; i--) {
        out[i] = (magnitude & 1) ? '1' : '0';
        magnitude >>= 1;
    }
    out[32] = '\0';
}
void to_ones_complement(int32_t n, char *out) {
    if (n >= 0) {
        out[0] = '0';
    }else {
        out[0] = '1';
        n = -n;
    }
    for (int i = 31; i >= 0; i--) {
        out[i] = (n >> (32-i)) & 1 ? '1' : '0';
    }
    out[32] = '\0';
}
void to_twos_complement(int32_t n, char *out) {
    uint32_t val;

    if (n >= 0) {
        val =(int32_t)n;
    }else {
        val = (uint32_t)(-n);
        val = ~val + 1;
    }

    for (int i = 31; i >= 0; i--) {
        out[31 - i] = (val >> i) & 1 ? '1' : '0';
    }
    out[32] = '\0';
}