#include <stdio.h>
#include <string.h>
#include "stretchy_buffer.h"

#define MAX_LEN 256
#define PREAMBLE 25

int *nums = NULL;
void move_nums_down() {
    for (int i = 1; i < PREAMBLE; i++) {
        nums[i-1] = nums[i];
    }
}

int main() {
    FILE *input = fopen("input", "r");
    if (input == NULL) {
        fprintf(stderr, "Failed to open file.\n");
        exit(1);
    }

    char buffer[MAX_LEN] = { 0 }; 

    // stb stretchy_buffer resizable array
    char **arr = NULL;

    for (int i = 0; fgets(buffer, MAX_LEN, input); i++) {
        sb_add(arr, 1);
        arr[i] = malloc(MAX_LEN);
        strcpy(arr[i], buffer);
    }

    for (int i = 0; i < PREAMBLE; i++) {
        sb_push(nums, atoi(arr[i]));
    }

    int bad_num = -1;
    for (int i = PREAMBLE; i < sb_count(arr); i++) {
        int match_found = 0;
        for (int j = 0; j < sb_count(nums); j++) {
            for (int k = 1; k < sb_count(nums); k++) {
                if (nums[j] + nums[k] == atoi(arr[i])) {
                    match_found = 1;
                }
            }
        }

        if (!match_found) {
            bad_num = atoi(arr[i]);
            break;
        }

        move_nums_down();
        nums[PREAMBLE - 1] = atoi(arr[i]);
    }
    printf("%i\n", bad_num);

    for (int i = 0; i < sb_count(arr); i++) {
        free(arr[i]);
    }
    sb_free(arr);
    sb_free(nums);
    fclose(input);
    return 0;
}

