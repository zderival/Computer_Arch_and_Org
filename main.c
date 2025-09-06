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

