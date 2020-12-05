#include <stdio.h>
#include <string.h>
#include <limits.h>
#include "stretchy_buffer.h"

#define MAX_LEN 12

int main() {
    // Grab Input
    FILE *input = fopen("input", "r");
    if (input == NULL) {
        fprintf(stderr, "Failed to open file.\n");
        exit(1);
    }

    // stb stretchy_buffer resizable array
    char **arr = NULL;
    char buffer[MAX_LEN] = { 0 }; 
    for (int i = 0; fgets(buffer, MAX_LEN, input); i++) {
        sb_add(arr, 1);
        arr[i] = malloc(MAX_LEN);
        strcpy(arr[i], buffer);
    }

    // Puzzle Start
    int max_id = INT_MIN;
    for (int i = 0; i < sb_count(arr); i++) {
        int min = 0, max = 127, row, column;
        for (int j = 0; j < 10; j++) {
            int half = (((max+1) - min) / 2);
            if (j < 6) {
                // F | B
                if (arr[i][j] == 'F') {
                    max -= half;
                } else {
                    min += half;
                }
            } else if (j == 6) {
                if (arr[i][j] == 'F') {
                    row = min;
                } else {
                    row = max;
                }
                min = 0;
                max = 7;
            } else if (j < 9) {
                // R | L
                if (arr[i][j] == 'L') {
                    max -= half;
                } else {
                    min += half;
                }
            } else {
                if (arr[i][j] == 'L') {
                    column = min;
                } else {
                    column = max;
                }
            }
        }

        int id = (row * 8) + column;
        if (id > max_id) {
            max_id = id;
        }
    }
    printf("%i\n", max_id);

    // Cleanup
    for (int i = 0; i < sb_count(arr); i++) {
        free(arr[i]);
    }

    sb_free(arr);
    fclose(input);
    return 0;
}

