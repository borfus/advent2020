#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stretchy_buffer.h"

#define MAX_LEN 256

int main() {
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

    int correct_passwords = 0;
    for (int i = 0; i < sb_count(arr); i++) {
        int min, max;
        char c, password[MAX_LEN];
        sscanf(arr[i], "%i-%i %c: %s\n", &min, &max, &c, password);

        if ((password[min-1] == c || password[max-1] == c) && password[min-1] != password[max-1]) {
            correct_passwords++;
        }
    }
    printf("%i\n", correct_passwords);

    for (int i = 0; i < sb_count(arr); i++) {
        free(arr[i]);
    }
    sb_free(arr);
    fclose(input);
    return 0;
}

