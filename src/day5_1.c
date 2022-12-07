#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUM_OF_STACKS 9
#define NUM_OF_MOVES 501
#define NUM_OF_CRATES 56
#define NUM_OF_CHARS_LINE 36
#define MAX_IN_STACK 9

struct crate_t {
    char type;
    struct crate_t* next_crate;
    struct crate_t* prev_crate;
};
typedef struct crate_t crate_t;

crate_t* make_crate(void) {
    crate_t* crate_ptr = malloc(sizeof(crate_t) * (NUM_OF_CRATES + NUM_OF_STACKS));
    if (crate_ptr == NULL) {
        printf("Allocation of crates failed");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < NUM_OF_CRATES + NUM_OF_STACKS; i++) {
        crate_ptr[i].type = '$';
        crate_ptr[i].next_crate = NULL;
        crate_ptr[i].prev_crate = NULL;
    }
    return crate_ptr;
}

int crates_in_stack(FILE* file, int stack_number) {
    int num_of_crates = 0;
    char c = '+';
    for (int i = 0; i <= MAX_IN_STACK; i++) {
        fseek(file,
              (NUM_OF_CHARS_LINE * MAX_IN_STACK) - (NUM_OF_CHARS_LINE * (i + 1)) +
                  (1 + 4 * stack_number),
              SEEK_SET);
        c = fgetc(file);
        if (c >= 65 && c <= 90 || c >= 49 && c <= 57) {
            num_of_crates++;
        }
    }
    printf("num in stack %d: %d\n", stack_number + 1, num_of_crates);
    fseek(file, 0, SEEK_SET);
    return num_of_crates;
}

void assign_crates(crate_t* crate, FILE* file) {
    char crate_type = '~';
    int crates_in_row = 0, num_crate = 0;
    for (int j = 0; j < NUM_OF_STACKS; j++) {
        crates_in_row = crates_in_stack(file, j);
        for (int i = 1; i <= crates_in_row; i++) {
            fseek(file, (NUM_OF_CHARS_LINE * NUM_OF_STACKS) - (NUM_OF_CHARS_LINE * i) + (1 + 4 * j),
                  SEEK_SET);
            crate_type = fgetc(file);
            crate[num_crate].type = crate_type;
            crate[num_crate].next_crate = NULL;
            crate[num_crate].prev_crate = NULL;
            num_crate++;
        }
    }
}

void chain_crates(crate_t* crate) {
    int max_crates = NUM_OF_CRATES + NUM_OF_STACKS;
    crate[0].next_crate = &crate[1];
    crate[max_crates - 1].prev_crate = &crate[max_crates - 2];

    for (int i = 1; i < NUM_OF_CRATES + NUM_OF_STACKS - 1; i++) {
        crate[i].next_crate = &crate[i + 1];
        crate[i].prev_crate = &crate[i - 1];
    }
}

void move_crates(crate_t* crate, FILE* file) {
    int num_to_move;
    char source, dest;
    crate_t* temp_ptr1;
    crate_t* first_crate = crate;
    for (int i = 0; i < NUM_OF_MOVES; i++) {
        fscanf(file, "move %d from %c to %c\n", &num_to_move, &source, &dest);
        for (int j = 0; j < num_to_move; j++) {
            while (crate->next_crate != NULL && crate->next_crate->type != source + 1) { // dest
                crate = crate->next_crate;
            }
            temp_ptr1 = crate;
            if (crate->next_crate == NULL) {
                crate->prev_crate->next_crate = NULL;
            } else {
                crate->prev_crate->next_crate = crate->next_crate;
                crate->next_crate->prev_crate = crate->prev_crate;
            }
            crate = first_crate;

            while (crate->next_crate != NULL && crate->next_crate->type != dest + 1) {
                crate = crate->next_crate;
            }
            if (crate->next_crate == NULL) {
                temp_ptr1->next_crate = NULL;
                temp_ptr1->prev_crate = crate;
                crate->next_crate = temp_ptr1;
            } else {
                temp_ptr1->next_crate = crate->next_crate;
                temp_ptr1->prev_crate = crate;
                crate->next_crate->prev_crate = temp_ptr1;
                crate->next_crate = temp_ptr1;
            }
            crate = first_crate;
        }
    }
}

void print_list(crate_t* crate) {
    char c;
    while (crate->type != '1') {
        crate = crate->prev_crate;
    }
    while (crate != NULL) {
        if (crate->next_crate != NULL && crate->next_crate->type >= 49 &&
            crate->next_crate->type <= 57) {
            c = crate->type;
            printf("%c\n", c);
            crate = crate->next_crate;
        } else {
            c = crate->type;
            printf("%c ", c);
            crate = crate->next_crate;
        }
    }
}

int main() {
    FILE* fp_crates = fopen("day5_crates.txt", "r");
    if (fp_crates == NULL) {
        printf("Crates could not be opened");
        exit(EXIT_FAILURE);
    }
    FILE* fp_moves = fopen("day5_move_crates.txt", "r");
    if (fp_moves == NULL) {
        printf("Moves could not be opened");
        exit(EXIT_FAILURE);
    }

    crate_t* crate = make_crate();
    if (crate == NULL) {
        printf("Crates were not created");
        exit(EXIT_FAILURE);
    }

    assign_crates(crate, fp_crates);
    chain_crates(crate);
    move_crates(crate, fp_moves);
    print_list(crate);

    free(crate);
    fclose(fp_crates);
    fclose(fp_moves);
}