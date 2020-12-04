#include <stdio.h>
#include <stdlib.h>
#include "stretchy_buffer.h"

#define MAX_LEN 256

int main() {
    FILE *input = fopen("input", "r");
    if (input == NULL) {
        fprintf(stderr, "Failed to open file.\n");
        exit(1);
    }

    // STB stretchy_buffer resizable array
    int *arr = NULL;
    char buffer[MAX_LEN];

    for (int i = 0; fgets(buffer, MAX_LEN, input) != NULL; i++) {
        sb_push(arr, atoi(buffer));
    }

    for (int i = 0; i < sb_count(arr); i++) {
        for (int j = 0; j < sb_count(arr); j++) {
            if (arr[i] + arr[j] == 2020) {
                printf("%i * %i: %i\n", arr[i], arr[j], arr[i] * arr[j]);
                sb_free(arr);
                fclose(input);
                return 0;
            }
        }
    }

    sb_free(arr);
    fclose(input);
    return 0;
}

