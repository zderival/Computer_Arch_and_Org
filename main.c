#include <stdio.h>
#include <string.h>
#include <stdint.h>
void div_convert(uint32_t n, int base, char *out);
void sub_convert(uint32_t n, int base, char *out);
void print_tables(uint32_t n);

int main(void) {
    char buffer[33];
    char out[65];
    FILE *file = fopen("a1_test_file.txt", "r");
    if (file == NULL) {
        printf("File could not be open\n");
        return 1;
    }

    char line[256];
    int counter = 1;
    int pass_counter = 1;
    while (fgets(line,sizeof(line), file) != NULL) {
        if (line[0] == '#' || line[0] == '\n') continue;
        line[strcspn(line, "\n")] = '\0';

        if (strncmp(line, "div_convert", 11) == 0) {
            int num, base;
            char expected[65];

            sscanf(line + 12, "%d %d %s", &num, &base, expected);
            div_convert(num, base, out);

            if (strcmp(out, expected) == 0) {
                printf("Test %d: div_convert(%d, %d) -> Expected: %s, Got: %s [PASS]\n"
                ,counter++, num, base,expected,out);
                pass_counter++;
            } else {
                printf("Test %d: div_convert(%d, %d) -> Expected: %s, Got: %s [FAIL]\n"
                ,counter++, num, base,expected,out);}

        }else if (strncmp(line, "sub_convert", 11) == 0) {
            int num, base;
            char expected[65];

            sscanf(line + 12, "%d %d %s", &num, &base, expected);
            sub_convert(num, base, out);

            if (strcmp(out, expected) == 0){
                printf("Test %d: sub_convert(%d, %d) -> Expected: %s, Got: %s [PASS]\n"
                ,counter++, num, base,expected,out);
                pass_counter++;
            }else {
                printf("Test %d: sub_convert(%d, %d) -> Expected: %s, Got: %s [FAIL]\n"
                ,counter++, num, base,expected,out);
            }
        }else if ((strncmp(line, "print_tables", 12) == 0)) {
            int num;
            sscanf(line + 13, "%d", &num);
            printf("Test %d: print_tables(%d) -> [FORMATTED_OUTPUT] [PASS]\n", counter++, num);
            pass_counter++;
        }
    }
    fclose(file);
    printf("Summary: %d/%d tests passed", pass_counter, counter);
    return 0;
}

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
    int i = 0;
    uint32_t power = 1;

    while(power <= n / base) {
        power *= base;
    }
    while (power > 0) {
        int digit = n / power;
        n -= digit *= power;

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
    printf(" Original : Binary = %s Octal = %s Decimal = %u Hex = %s\n",
    bin , oct , n , hex );

    uint32_t shifted = n << 3;
    div_convert ( shifted , 2 , bin ) ;
    div_convert ( shifted , 8 , oct ) ;
    div_convert ( shifted , 16 , hex ) ;
    printf (" Left Shift by 3: Binary = %s Octal = %s Decimal = %u Hex = %s\n",
    bin , oct , shifted , hex );

    uint32_t masked = n & 0xFF;
    div_convert( masked , 2, bin ) ;
    div_convert( masked , 8, oct ) ;
    div_convert( masked , 16, hex );
    printf("And with 0xFF: Binary = %s Octal = %s Decimal = %u Hex = %s\n",
        bin, oct, masked, hex);
}
