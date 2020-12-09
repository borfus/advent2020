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

    for (int i = 0; fgets(buffer, MAX_LEN, input); i++) {
        sb_add(arr, 1);
        arr[i] = malloc(MAX_LEN);
        strcpy(arr[i], buffer);
        sb_push(count, 0);
    }

    // Puzzle Start
    int accumulator = 0, not_found = 1, skip = 0, skipped = 0, skip_count = 0;
    while (not_found) {
        int i = 0, duplicate = 0;
        while (i < sb_count(arr)) {
            if (count[i] == 1) {
                printf("DUPLICATE FOUND!\n");
                duplicate = 1;
                accumulator = 0;
                skip++;
                skipped = 0;
                skip_count = 0;
                for (int j = 0; j < sb_count(count); j++) {
                    count[j] = 0;
                }
                break;
            }
            count[i] = 1;

            int arg;
            char sign, command[4];
            sscanf(arr[i], "%3s %c%i\n", command, &sign, &arg);
            
            if (strcmp(command, "nop") == 0 || strcmp(command, "jmp") == 0) {
                if (skip_count == skip && skipped == 0) {
                    if (strcmp(command, "nop") == 0) {
                        strcpy(command, "jmp");
                    } else {
                        strcpy(command, "nop");
                    }
                    skipped = 1;
                } else {
                    skip_count++;
                }
            }

            if (sign == '-') {
                arg *= -1;
            }

            printf("Line %5i: %s %i\n", i+1, command, arg);

            if (strcmp(command, "acc") == 0) {
                accumulator += arg;
                i++;
            } else if (strcmp(command, "jmp") == 0) {
                i += arg;
            } else {
                i++;
            }
        }

        if (!duplicate) {
            not_found = 0;
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
