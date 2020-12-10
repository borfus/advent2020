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
    int onejolt = 0, threejolt = 0;
    for (int i = 0; i < sb_count(arr); i++) {
        int result = arr[i] - arr[i-1];

        if (result == 1) {
            onejolt++;
        } else if (result == 3) {
            threejolt++;
        }
    }
    printf("%i\n", onejolt * threejolt);

    sb_free(arr);
    fclose(input);
    return 0;
}

