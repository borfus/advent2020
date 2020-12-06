#include <stdio.h>
#include <string.h>
#include "stretchy_buffer.h"

#define MAX_LEN 256

// stb stretchy_buffer resizable array
char **arr = NULL;

int main() {
    FILE *input = fopen("input", "r");
    if (input == NULL) {
        fprintf(stderr, "Failed to open file.\n");
        exit(1);
    }

    char buffer[MAX_LEN] = { 0 }; 

    for (int i = 0; fgets(buffer, MAX_LEN, input); i++) {
        sb_add(arr, 1);
        arr[i] = malloc(MAX_LEN);
        strcpy(arr[i], buffer);
    }

    // Puzzle Start
    char **answers = NULL;
    int sum = 0;
    for (int i = 0; i < sb_count(arr); i++) {
        if (strcmp(arr[i], "\n") == 0) {
            for (int j = 0; j < sb_count(answers); j++) {
                if (answers[j][1] == '1') {
                    sum++;
                }
                free(answers[j]);
            }
            sb_free(answers);
            answers = NULL;
        } else {
            if (sb_count(answers) == 0) {
                for (int j = 0; j < strlen(arr[i]) - 1; j++) {
                    char ans_map[3] = { 0 };
                    ans_map[0] = arr[i][j];
                    ans_map[1] = '1';

                    sb_add(answers, 1);
                    answers[j] = malloc(3);
                    strcpy(answers[j], ans_map);
                }
            } else {
                for (int j = 0; j < sb_count(answers); j++) {
                    int included = 0;
                    for (int k = 0; k < strlen(arr[i]); k++) {
                        if (answers[j][0] == arr[i][k]) {
                            included = 1;
                            break;
                        }
                    }
                    if (!included) {
                        answers[j][1] = '0';
                    }
                }
            }
        }
    }
    printf("%i\n", sum);

    for (int i = 0; i < sb_count(arr); i++) {
        free(arr[i]);
    }
    sb_free(arr);
    fclose(input);
    return 0;
}
