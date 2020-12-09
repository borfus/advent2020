#include <stdio.h>
#include <string.h>
#include "stretchy_buffer.h"

#define MAX_LEN 256

int main() {
    FILE *input = fopen("input", "r");
    if (input == NULL) {
        fprintf(stderr, "Failed to open file.\n");
        exit(1);
    }

    char buffer[MAX_LEN] = { 0 }; 

    // stb stretchy_buffer resizable array
    char **arr = NULL;
    int *count = NULL;
    int accumulator = 0;

    for (int i = 0; fgets(buffer, MAX_LEN, input); i++) {
        sb_add(arr, 1);
        arr[i] = malloc(MAX_LEN);
        strcpy(arr[i], buffer);
        sb_push(count, 0);
    }

    // Puzzle Start
    int i = 0;
    while (i < sb_count(arr)) {
        printf("Line #%i: %s", i+1, arr[i]);
        if (count[i] == 1) {
            printf("DUPLICATE FOUND!\n");
            break;
        }
        count[i] = 1;

        int arg;
        char sign, command[4];
        sscanf(arr[i], "%3s %c%i\n", command, &sign, &arg);

        if (sign == '-') {
            arg *= -1;
        }

        if (strcmp(command, "acc") == 0) {
            accumulator += arg;
            i++;
        } else if (strcmp(command, "jmp") == 0) {
            i += arg;
        } else {
            i++;
        }
    }

    printf("%i\n", accumulator);

    for (int i = 0; i < sb_count(arr); i++) {
        free(arr[i]);
    }
    sb_free(arr);
    sb_free(count);
    fclose(input);
    return 0;
}
