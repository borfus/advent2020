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
    char *answers = NULL;
    int sum = 0;
    for (int i = 0; i < sb_count(arr); i++) {
        if (strcmp(arr[i], "\n") == 0) {
            sum += sb_count(answers);
            sb_free(answers);
            answers = NULL;
        } else {
            for (int j = 0; j < strlen(arr[i]); j++) {
                if (arr[i][j] == '\n') { break; }
                int included = 0;

                for (int k = 0; k < sb_count(answers); k++) {
                    if (answers[k] == arr[i][j]) {
                        included = 1;
                    }
                }

                if (!included) {
                    sb_push(answers, arr[i][j]);
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
