#include <stdio.h>
#include <string.h>
#include "stretchy_buffer.h"

#define MAX_LEN 256

int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

int main() {
    FILE *input = fopen("input", "r");
    if (input == NULL) {
        fprintf(stderr, "Failed to open file.\n");
        exit(1);
    }

    char buffer[MAX_LEN] = { 0 }; 

    // stb stretchy_buffer resizable array
    int *arr = NULL;
    sb_push(arr, 0);
    for (int i = 0; fgets(buffer, MAX_LEN, input); i++) {
        sb_push(arr, atoi(buffer));
    }
    qsort(arr, sb_count(arr), sizeof(int), compare);
    sb_push(arr, arr[sb_count(arr) - 1] + 3);

    // Puzzle Start
    long long *paths = NULL;
    sb_add(paths, arr[sb_count(arr) - 1] + 1);
    paths[0] = 1;

    for (int i = 1; i < sb_count(paths); i++) {
        for (int j = 1; j < 4; j++) {
            for (int k = 0; k < sb_count(arr); k++) {
                if (arr[k] == i - j) {
                    paths[i] += paths[i - j];
                    continue;
                }
            } 
        }
    }

    printf("%lli\n", paths[sb_count(paths) - 1]);

    sb_free(paths);
    sb_free(arr);
    fclose(input);
    return 0;
}

