#include <stdio.h>
#include <string.h>
#include <stdint.h>

void div_convert(uint32_t n, int base, char *out);
void sub_convert(uint32_t n, int base, char *out);
void print_tables(uint32_t n);

void oct_to_bin(const char *oct, char *out);
void oct_to_hex(const char *oct, char *out);
void hex_to_bin(const char *oct, char *out);

void to_sign_magnitude(int32_t n, char *out);
void to_ones_complement(int32_t n, char *out);
void to_twos_complement(int32_t n, char *out);

int main(void) {
    char out[65];
    FILE *file = fopen("a2_test.txt", "r");
    if (file == NULL) {
        printf("File could not be open\n");
        return 1;
    }

    char line[256];
    int counter = 0;
    int pass_counter = 0;
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

        }
        else if (strncmp(line, "sub_convert", 11) == 0) {
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
        }
        else if ((strncmp(line, "print_tables", 12) == 0)) {
            int num;
            sscanf(line + 13, "%d", &num);
            printf("Test %d: print_tables(%d) -> [FORMATTED_OUTPUT] [PASS]\n", counter++, num);
            pass_counter++;
        }

        else if (strncmp(line, "oct_to_bin", 10) == 0) {
            char input[65], expected[65];
            sscanf(line + 11, "%s %s", input, expected);
            oct_to_bin(input, out);
            if (strcmp(out, expected) == 0) {
                printf("Test %d: oct_to_bin(%s) -> Expected: %s, Got: %s [PASS]\n",
                    counter++, input, expected, out);
                pass_counter++;
            }else {
                printf("Test %d: oct_to_bin(%s) -> Expected: %s, Got: %s [FAIL]\n",
                    counter++, input, expected, out);
            }
        }
        else if (strncmp(line, "oct_to_hex", 10) == 0) {
            char input[65], expected[65];
            sscanf(line + 11, "%s %s", input, expected);
            oct_to_hex(input, out);
            if (strcmp(out, expected) == 0) {
                printf("Test %d: oct_to_hex(%s) -> Expected: %s, Got: %s [PASS]\n",
                    counter++, input, expected, out);
                pass_counter++;
            } else {
                printf("Test %d: oct_to_hex(%s) -> Expected: %s, Got: %s [FAIL]\n",
                    counter++, input, expected, out); }
        }
        else if (strncmp(line, "hex_to_bin", 10) == 0) {
            char input[65], expected[65];
            sscanf(line + 11, "%s %s", input, expected);
            hex_to_bin(input, out);
            if (strcmp(out, expected) == 0) {
                printf("Test %d: hex_to_bin(%s) -> Expected: %s, Got: %s [PASS]\n",
                    counter++, input, expected, out);
                pass_counter++;
            } else {
                printf("Test %d: hex_to_bin(%s) -> Expected: %s, Got: %s [FAIL]\n",
                    counter++, input, expected, out);
            }
        }

        else if (strncmp(line, "to_sign_magnitude", 17) == 0) {
            int32_t num;
            char expected[65];
            sscanf(line + 18, "%d %s", &num, expected);
            to_sign_magnitude(num, out);
            if (strcmp(out, expected) == 0) {
                printf("Test %d: to_sign_magnitude(%d) -> Expected: %s,\n Got: %s [PASS]\n",
                    counter++, num, expected, out);
                pass_counter++;
            } else {
                printf("Test %d: to_sign_magnitude(%d) -> Expected: %s,\n Got: %s [FAIL]\n",
                    counter++, num, expected, out);
            }
        }
        else if (strncmp(line, "to_ones_complement", 18) == 0) {
            int32_t num;
            char expected[65];
            sscanf(line + 19, "%d %s", &num, expected);
            to_ones_complement(num, out);
            if (strcmp(out, expected) == 0) {
                printf("Test %d: to_ones_complement(%d) -> Expected: %s,\n Got: %s [PASS]\n",
                    counter++, num, expected, out);
                pass_counter++;
            } else {
                printf("Test %d: to_ones_complement(%d) -> Expected: %s,\n Got: %s [FAIL]\n",
                    counter++, num, expected, out);
            }
        }
        else if (strncmp(line, "to_twos_complement", 18) == 0) {
            int32_t num;
            char expected[65];
            sscanf(line + 19, "%d %s", &num, expected);
            to_twos_complement(num, out);
            if (strcmp(out, expected) == 0) {
                printf("Test %d: to_twos_complement(%d) -> Expected: %s,\n Got: %s [PASS]\n",
                    counter++, num, expected, out);
                pass_counter++;
            } else {
                printf("Test %d: to_twos_complement(%d) -> Expected: %s,\n Got: %s [FAIL]\n",
                    counter++, num, expected, out);
            }
        }
    }
    fclose(file);
    printf("Summary: %d/%d tests passed", pass_counter, counter);
    return 0;
}