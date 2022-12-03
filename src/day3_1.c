#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int scan_line_size(FILE* fp);
char cmp_strings(char* string, int string_size);
char shared_letters(const char* string1, const char* string2);
int item_prio(char* letter, char* array);
int scan_num_of_sacks(FILE* file);

int main() {
    char lc_item[26] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm',
                        'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
    char uc_item[26] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M',
                        'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
    int line_size = 1, priority = 0;
    char string[50];
    char shared;

    FILE* fp = fopen("day3_rucksack.txt", "r");
    if (fp == NULL) {
        printf("Failed to open file.\n");
        exit(EXIT_FAILURE);
    }

    int num_of_sacks = scan_num_of_sacks(fp);

    fseek(fp, 0, SEEK_SET);

    for (int i = 0; i <= num_of_sacks; i++) {
        line_size = scan_line_size(fp);
        fscanf(fp, "%s", string);
        shared = cmp_strings(string, line_size);

        if (shared >= 65 && shared <= 90) {
            priority += item_prio(&shared, uc_item);
            priority += 26;
        } else {
            priority += item_prio(&shared, lc_item);
        }

        if (i < num_of_sacks) {
            fgetc(fp);
        }

        if (i == num_of_sacks - 1) {
            printf("error?");
        }
    }

    printf("accumulated prio: \n%d\n", priority);

    fclose(fp);
    return 0;
}

int scan_line_size(FILE* fp) {
    int i = 0;
    char c = '0';
    do {
        c = getc(fp);
        if (c != '\n' && c != EOF) {
            i++;
        }

    } while (c != '\n' && c != EOF);

    if (i <= 0) {
        printf("String was not read");
        exit(EXIT_FAILURE);
    }

    fseek(fp, (-i - 1), SEEK_CUR);
    return i;
}

char cmp_strings(char* string, int string_size) {
    int split_string = (string_size / 2);
    if (split_string <= 0) {
        printf("Invalid string size");
        exit(EXIT_FAILURE);
    }

    char ch = '0', temp1[split_string + 1], temp2[split_string + 1];

    strncpy(temp1, string, split_string);
    temp1[split_string] = '\0';
    strncpy(temp2, &string[split_string], split_string);
    temp2[split_string] = '\0';
    ch = shared_letters(temp1, temp2);

    return ch;
}

char shared_letters(const char* string1, const char* string2) {
    if (string1 == NULL || string2 == NULL) {
        return '0';
    }

    int count[256] = {0};

    printf("Shared letters between '%s' and '%s' equals: = ", string1, string2);

    while (*string1) {
        count[*string1++]++;
    }

    while (*string2) {
        if (count[*string2] > 0) {
            printf("%c\n", *string2);
            return *string2;
        }
        string2++;
    }
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