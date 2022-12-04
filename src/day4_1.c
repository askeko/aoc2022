#include <stdio.h>
#include <stdlib.h>

#define NUM_OF_PAIRS 1000

typedef struct cleaner_pair_t {
    int elf1_low;
    int elf1_up;
    int elf2_low;
    int elf2_up;
} cleaner_pair_t;

void open_file(FILE* fp);
void scan_cleaners(FILE* fp, cleaner_pair_t* cleaners);
int check_same_range(cleaner_pair_t* cleaners);
int check_overlap(cleaner_pair_t* cleaners);

int main() {
    FILE* fp = fopen("day4_cleaners.txt", "r");
    if (fp == NULL) {
        printf("Cannot open file.\n");
        exit(EXIT_FAILURE);
    }

    cleaner_pair_t* cleaners = malloc(sizeof(cleaner_pair_t) * NUM_OF_PAIRS);
    if (cleaners == NULL) {
        printf("Could not find cleaners\n");
        exit(EXIT_FAILURE);
    }

    scan_cleaners(fp, cleaners);
    int contains_same_range = check_same_range(cleaners);
    int overlaps = check_overlap(cleaners);
    printf("%d assignments contain the same range\n", contains_same_range);
    printf("%d assignments overlap\n", overlaps);

    fclose(fp);
    free(cleaners);

    return 0;
}

void scan_cleaners(FILE* fp, cleaner_pair_t* cleaners) {
    for (int i = 0; i < NUM_OF_PAIRS; i++) {
        fscanf(fp, "%d-%d,%d-%d", &cleaners[i].elf1_low, &cleaners[i].elf1_up,
               &cleaners[i].elf2_low, &cleaners[i].elf2_up);
    }
}

int check_same_range(cleaner_pair_t* cleaners) {
    int contains_same_range = 0;
    for (int i = 0; i < NUM_OF_PAIRS; i++) {
        if (cleaners[i].elf1_low >= cleaners[i].elf2_low &&
            cleaners[i].elf1_up <= cleaners[i].elf2_up) {
            contains_same_range++;
        } else if (cleaners[i].elf2_low >= cleaners[i].elf1_low &&
                   cleaners[i].elf2_up <= cleaners[i].elf1_up) {
            contains_same_range++;
        }
    }

    return contains_same_range;
}

int check_overlap(cleaner_pair_t* cleaners) {
    int overlaps = 0;
    for (int i = 0; i < NUM_OF_PAIRS; i++) {
        if (cleaners[i].elf1_low >= cleaners[i].elf2_low &&
            cleaners[i].elf1_low <= cleaners[i].elf2_up) {
            overlaps++;
        } else if (cleaners[i].elf1_up >= cleaners[i].elf2_low &&
                   cleaners[i].elf1_low <= cleaners[i].elf2_up) {
            overlaps++;
        } else if (cleaners[i].elf2_low >= cleaners[i].elf1_low &&
                   cleaners[i].elf2_low <= cleaners[i].elf1_up) {
            overlaps++;
        } else if (cleaners[i].elf2_low >= cleaners[i].elf1_low &&
                   cleaners[i].elf2_low <= cleaners[i].elf1_up) {
            overlaps++;
        }
    }

    return overlaps;
}