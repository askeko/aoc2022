#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char cmp_strings(char* string1, char* string2, char* string3);
char shared_letters(const char* string1, const char* string2, const char* string3);
int item_prio(char* letter, char* array);
int scan_num_of_sacks(FILE* file);

int main() {
    char lc_item[26] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm',
                        'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
    char uc_item[26] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M',
                        'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
    int line_size = 1, priority = 0;
    char string1[50], string2[50], string3[50];
    char shared;

    FILE* fp = fopen("day3_rucksack.txt", "r");
    if (fp == NULL) {
        printf("Failed to open file.\n");
        exit(EXIT_FAILURE);
    }

    int num_of_sacks = scan_num_of_sacks(fp) / 3;

    fseek(fp, 0, SEEK_SET);

    for (int i = 0; i <= num_of_sacks; i++) {
        fscanf(fp, "%s", string1);
        fscanf(fp, "%s", string2);
        fscanf(fp, "%s", string3);
        shared = cmp_strings(string1, string2, string3);

        if (shared >= 65 && shared <= 90) {
            priority += item_prio(&shared, uc_item);
            priority += 26;
        } else {
            priority += item_prio(&shared, lc_item);
        }

        if (i < num_of_sacks) {
            fgetc(fp);
        }
    }

    printf("\naccumulated prio: %d\n", priority);

    fclose(fp);
    return 0;
}

char cmp_strings(char* string1, char* string2, char* string3) {
    char ch = '0';
    ch = shared_letters(string1, string2, string3);
    return ch;
}

char shared_letters(const char* string1, const char* string2, const char* string3) {
    if (string1 == NULL || string2 == NULL || string3 == NULL) {
        return '0';
    }

    int count[256] = {0};

    printf("Shared letters between '%s' and '%s' and '%s' equals: = ", string1, string2, string3);

    while (*string1) {
        count[*string1++]++;
    }

    while (*string2) {
        count[*string2++]++;
    }
    
    while (*string3) {
        if (count[*string3] > 0) {
            printf("%c\n", *string3);
            return *string3;
        }
        string3++;
    }
/*
    while (*string2) {
        if (count[*string2] > 0) {
            while (*string3) {
                if (count[*string3] > 0) {
                    printf("%c\n", *string3);
                    return *string3;
                }
                string3++;
            }
        }
        string2++;
    }
*/
    return '0';
}

int item_prio(char* letter, char* array) {
    int i = 0;
    while (*letter != array[i]) {
        i++;
    }

    return i + 1;
}

int scan_num_of_sacks(FILE* file) {
    char c;
    int num_of_sacks = 0;
    while ((c = getc(file)) != EOF) {
        if (c == '\n') {
            num_of_sacks++;
        }
    }
    return num_of_sacks;
}