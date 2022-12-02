#include <stdio.h>
#include <stdlib.h>

void scan_hand(FILE* file, char* my_hand, char* opp_hand);
void eval_round(int* score, char my_hand, char opp_hand);
void print_final_score(int accumulated_score);
int scan_num_of_rounds(FILE* file);

int main() {
    FILE* fp = fopen("day2_strats.txt", "r");
    if (fp == NULL) {
        printf("ERROR: Failed to open file");
        exit(EXIT_FAILURE);
    }

    char my_hand, opp_hand;
    int score = 0;
    int num_of_rounds;

    num_of_rounds = scan_num_of_rounds(fp) + 1;
    fseek(fp, 0, SEEK_SET);

    for (int i = 0; i < num_of_rounds; i++) {
        scan_hand(fp, &my_hand, &opp_hand);
        printf("my_hand: %c\n", my_hand);
        printf("opp_hand: %c\n", opp_hand);
        eval_round(&score, my_hand, opp_hand);
        printf("Score is: %d\n", score);
    }
}

void scan_hand(FILE* file, char* my_hand, char* opp_hand) {
    *opp_hand = getc(file);
    fseek(file, 1, SEEK_CUR);
    *my_hand = getc(file);
    fseek(file, 1, SEEK_CUR);
}

/*
void eval_round(int* score, char my_hand, char opp_hand) {
    switch (my_hand) {
    case 'X':
        *score += 1;
        if (opp_hand == 'A') {
            *score += 3;
        } else if (opp_hand == 'B') {
            *score += 0;
        } else if (opp_hand == 'C') {
            *score += 6;
        } else {
            printf("ERROR: Invalid hand input");
            exit(EXIT_FAILURE);
        }
        break;
    case 'Y':
        *score += 2;
        if (opp_hand == 'A') {
            *score += 6;
        } else if (opp_hand == 'B') {
            *score += 3;
        } else if (opp_hand == 'C') {
            *score += 0;
        } else {
            printf("ERROR: Invalid hand input");
            exit(EXIT_FAILURE);
        }
        break;
    case 'Z':
        *score += 3;
        if (opp_hand == 'A') {
            *score += 0;
        } else if (opp_hand == 'B') {
            *score += 6;
        } else if (opp_hand == 'C') {
            *score += 3;
        } else {
            printf("ERROR: Invalid hand input");
            exit(EXIT_FAILURE);
        }
        break;
    default:
        printf("ERROR: Invalid hand input");
        exit(EXIT_FAILURE);
        break;
    }
}
*/

void eval_round(int* score, char my_hand, char opp_hand) {
    switch (opp_hand) {
    case 'A': // rock
        if (my_hand == 'X') {
            *score += 3;
        } else if (my_hand == 'Y') {
            *score += (3 + 1);
        } else if (my_hand == 'Z') {
            *score += (6 + 2);
        } else {
            printf("ERROR: Invalid hand input");
            exit(EXIT_FAILURE);
        }
        break;
    case 'B': // paper
        if (my_hand == 'X') {
            *score += 1;
        } else if (my_hand == 'Y') {
            *score += (3 + 2);
        } else if (my_hand == 'Z') {
            *score += (6 + 3);
        } else {
            printf("ERROR: Invalid hand input");
            exit(EXIT_FAILURE);
        }
        break;
    case 'C': // scissor
        if (my_hand == 'X') {
            *score += 2;
        } else if (my_hand == 'Y') {
            *score += (3 + 3);
        } else if (my_hand == 'Z') {
            *score += (6 + 1);
        } else {
            printf("ERROR: Invalid hand input");
            exit(EXIT_FAILURE);
        }
        break;
    default:
        break;
    }
}

void print_final_score(int accumulated_score) {
    printf("Your final score is: %d", accumulated_score);
}

int scan_num_of_rounds(FILE* file) {
    char c;
    int num_of_rounds = 0;
    while ((c = getc(file)) != EOF) {
        if (c == '\n') {
            num_of_rounds++;
        }
    }
    return num_of_rounds;
}