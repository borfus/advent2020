#include <stdio.h>
#include <string.h>
#include "stretchy_buffer.h"

#define MAX_LEN 256

// stb stretchy_buffer resizable array
char **arr = NULL;

struct key_val {
    char key[3];
    char value[256];
} entry;

int main() {
    // Open file and store contents into array
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

    //---------- Puzzle Start ----------//
    char req_fields[7][4] = {
        "byr",
        "iyr",
        "eyr",
        "hgt",
        "hcl",
        "ecl",
        "pid"
    };

    char **passport_components = NULL;
    int passports = 0;
    for (int i = 0; i < sb_count(arr); i++) {

        if (strcmp(arr[i], "\n") == 0) {
            // new passport

            char key[4], value[32];
            int key_count = 0;
            for (int j = 0; j < sb_count(passport_components); j++) {
                if (passport_components[j][0] == '\0') {
                    break;
                }
                sscanf(passport_components[j], "%3s:%s", key, value);

                for (int k = 0; k < 7; k++) {
                    if (strcmp(key, req_fields[k]) == 0) {
                        key_count++;
                        break;
                    }
                }
            }

            if (key_count >= 7) {
                passports++;
            }

            for (int j = 0; j < sb_count(passport_components); j++) {
                free(passport_components[j]);
            }
            sb_free(passport_components);
            passport_components = NULL;
        } else {
            char *ptr = strtok(arr[i], " ");
            for (int j = 0; ptr != NULL; j++) {
                if (ptr[strlen(ptr) - 1] == '\n') {
                    ptr[strlen(ptr) - 1] = '\0';
                }

                sb_add(passport_components, 1);
                passport_components[sb_count(passport_components) - 1] = malloc(MAX_LEN);
                strcpy(passport_components[sb_count(passport_components) - 1], ptr);
                ptr = strtok(NULL, " ");
            }
        }
    }
    
    printf("%i\n", passports);

    for (int i = 0; i < sb_count(arr); i++) {
        free(arr[i]);
    }

    sb_free(arr);
    fclose(input);
    return 0;
}

