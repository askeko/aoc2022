#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct elf_t {
    int calories;
} elf_t;

int main() {
    double time_spent = 0.0;
    clock_t begin = clock();
    char c;
    int num_of_elves = 0;

    FILE* fp;
    fp = fopen("day1_calories.txt", "r");
    if (fp == NULL) {
        printf("Could not open file");
        exit(EXIT_FAILURE);
    }

    while ((c = getc(fp)) != EOF) {
        if (c == '\n') {
            c = getc(fp);
            if (c == '\n') {
                num_of_elves++;
            }
        }
    }

    if (num_of_elves <= 0) {
        printf("Number of elves is less than or equal to 0. This should not happen! Exiting");
        exit(EXIT_FAILURE);
    }

    elf_t* elves = malloc(sizeof(elf_t) * num_of_elves);
    if (elves == NULL) {
        printf("Failed to allocate memory for elves. Exiting");
        exit(EXIT_FAILURE);
    }

    fseek(fp, 0, SEEK_SET);
    int temp = 0, calories = 0;
    for (int i = 0; i < num_of_elves;) {
        c = getc(fp);
        if (c == '\n') {
            c = getc(fp);
            if (c == '\n') {
                elves[i].calories = calories;
                calories = 0;
                temp = 0;
                i++;
            } else {
                fseek(fp, -1, SEEK_CUR);
            }
        } else {
            fseek(fp, -1, SEEK_CUR);
        }
        fscanf(fp, "%d", &temp);
        calories += temp;
    }
    int most_cal1 = 0, most_cal2 = 0, most_cal3 = 0;
    for (int i = 0; i < num_of_elves; i++) {
        if (elves[i].calories > most_cal1) {
            most_cal2 = most_cal1;
            most_cal3 = most_cal2;
            most_cal1 = elves[i].calories;
        } else if (elves[i].calories > most_cal2) {
            most_cal3 = most_cal2;
            most_cal2 = elves[i].calories;
        } else if (elves[i].calories > most_cal3) {
            most_cal3 = elves[i].calories;
        }
    }

    free(elves);
    fclose(fp);

    printf("There are %d elves\n", num_of_elves);
    printf("The elf carrying most calories is carrying: %d calories\n", most_cal1);
    printf("The elf carrying second most calories is carrying: %d calories\n", most_cal2);
    printf("The elf carrying third most calories is carrying: %d calories\n", most_cal3);
    int top3_cal = most_cal1 + most_cal2 + most_cal3;
    printf("They are carrying a total of %d calories\n", top3_cal);

    clock_t end = clock();

    // calculate elapsed time by finding difference (end - begin) and
    // dividing the difference by CLOCKS_PER_SEC to convert to seconds
    time_spent += (double)(end - begin) / CLOCKS_PER_SEC;

    printf("The elapsed time is %f seconds", time_spent);

    return 0;
}