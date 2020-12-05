#include <stdio.h>
#include <string.h>
#include <ctype.h>
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
    char req_eye_fields[7][4] = {
        "amb",
        "blu",
        "brn",
        "gry",
        "grn",
        "hzl",
        "oth"
    };

    char **passport_components = NULL;
    int passports = 0;
    for (int i = 0; i < sb_count(arr); i++) {

        if (strcmp(arr[i], "\n") == 0) {
            // new passport

            char key[4], value[32];
            int key_count = 0;
            for (int j = 0; j < sb_count(passport_components); j++) {
                sscanf(passport_components[j], "%3s:%s", key, value);

                if (strcmp(key, "byr") == 0) {
                    if (atoi(value) >= 1920 && atoi(value) <= 2002) {
                        key_count++;
                    }
                } else if (strcmp(key, "iyr") == 0) {
                    if (atoi(value) >= 2010 && atoi(value) <= 2020) {
                        key_count++;
                    }
                } else if (strcmp(key, "eyr") == 0) {
                    if (atoi(value) >= 2020 && atoi(value) <= 2030) {
                        key_count++;
                    }
                } else if (strcmp(key, "hgt") == 0) {
                    if (value[strlen(value) - 2] == 'i' && value[strlen(value) - 1] == 'n') {
                        char num[4] = { 0 };
                        if (strlen(value) == 5) {
                            strncpy(num, value, 3); 
                        } else {
                            strncpy(num, value, 2); 
                        }
                        if (atoi(num) >= 59 && atoi(num) <= 76) {
                            key_count++;
                        }
                    } else if (value[strlen(value) - 2] == 'c' && value[strlen(value) - 1] == 'm') {
                        char num[4] = { 0 };
                        if (strlen(value) == 5) {
                            strncpy(num, value, 3); 
                        } else {
                            strncpy(num, value, 2); 
                        }
                        if (atoi(num) >= 150 && atoi(num) <= 193) {
                            key_count++;
                        }
                    }
                } else if (strcmp(key, "hcl") == 0) {
                    if (strlen(value) == 7 && value[0] == '#') {
                        int alnum = 1;

                        for (int c = 1; c < 7; c++) {
                            if (!isalnum(value[c])) {
                                alnum = 0;
                            }
                        }

                        if (alnum) {
                            key_count++;
                        }
                    }
                } else if (strcmp(key, "ecl") == 0) {
                    for (int eye = 0; eye < 7; eye++) {
                        if (strcmp(value, req_eye_fields[eye]) == 0) {
                            key_count++;
                            break;
                        }
                    }
                } else if (strcmp(key, "pid") == 0) {
                    if (strlen(value) == 9) {
                        int isNum = 1;

                        for (int c = 0; c < 9; c++) {
                            if (!isdigit(value[c])) {
                                isNum = 0;
                            }
                        }

                        if (isNum) {
                            key_count++;
                        }
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

