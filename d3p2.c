#include <stdio.h>
#include <string.h>
#include "stretchy_buffer.h"

#define MAX_LEN 25600
#define MAX_BUF 256

// stb stretchy_buffer resizable array
char **arr = NULL;
char **src = NULL;

void extend() {
    for (int i = 0; i < sb_count(src); i++) {
        arr[i][strlen(arr[i]) - 1] = '\0';
        strcat(arr[i], src[i]);
    }
}

int main() {
    FILE *input = fopen("input", "r");
    if (input == NULL) {
        fprintf(stderr, "Failed to open file.\n");
        exit(1);
    }

    char buffer[MAX_BUF] = { 0 }; 

    for (int i = 0; fgets(buffer, MAX_BUF, input); i++) {
        sb_add(arr, 1);
        sb_add(src, 1);
        arr[i] = malloc(MAX_LEN);
        src[i] = malloc(MAX_BUF);
        strcpy(arr[i], buffer);
        strcpy(src[i], buffer);
    }

    long long product = 0;
    int x_path[5] = { 1, 3, 5, 7, 1 };
    int y_path[5] = { 1, 1, 1, 1, 2 };
    for (int i = 0; i < 5; i++) {
        int x = 0, y = 0, trees_hit = 0;
        while (y < sb_count(arr)) {
            x += x_path[i];
            y += y_path[i];

            if (x >= strlen(arr[0]) - 1) {
                extend();
            }

            if (y < sb_count(arr) && arr[y][x] == '#') {
                trees_hit++;
            }
        } 

        if (!product) {
            product = trees_hit;
        } else {
            product *= trees_hit;
        }
    }

    printf("%lli\n", product);

    sb_free(arr);
    fclose(input);
    return 0;
}

