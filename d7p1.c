#include <stdio.h>
#include <string.h>
#include "stretchy_buffer.h"

#define MAX_LEN 256

char **possible_bags = NULL;
void add_bag(char *string) {
    char bag[MAX_LEN] = { 0 };
    char *ptr = strtok(string, " ");
    for (int i = 0; ptr != NULL && i < 2; i++) {
        if (ptr[strlen(ptr) - 1] == '\n') {
            ptr[strlen(ptr) - 1] = '\0';
        }
        strcat(bag, ptr);
        if (i == 0) {
            strcat(bag, " ");
        }
        ptr = strtok(NULL, " ");
    }
    bag[strlen(bag)] = '\0';

    sb_add(possible_bags, 1);
    possible_bags[sb_count(possible_bags)-1] = malloc(MAX_LEN);
    strcpy(possible_bags[sb_count(possible_bags)-1], bag);
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

    // Puzzle Start
    char *my_bag = "shiny gold";
    char **checked_addresses = NULL;

    for (int pass = 0; pass < 100; pass++) {
        for (int i = 0; i < sb_count(arr); i++) {
            if (pass == 0) {
                char *p = strstr(arr[i], my_bag);
                if (p != NULL && p != arr[i]) {
                    sb_add(checked_addresses, 1);
                    checked_addresses[sb_count(checked_addresses) - 1] = malloc(MAX_LEN);
                    strcpy(checked_addresses[sb_count(checked_addresses) - 1], arr[i]);

                    add_bag(arr[i]);
                }
            } else { 
                for (int j = 0; j < sb_count(possible_bags); j++) {
                    char *p = strstr(arr[i], possible_bags[j]);
                    if (p != NULL) {
                        int included = 0;
                        for (int k = 0; k < sb_count(checked_addresses); k++) {
                            if (strcmp(checked_addresses[k], arr[i]) == 0) {
                                included = 1;
                            }
                        }

                        if (!included) {
                            sb_add(checked_addresses, 1);
                            checked_addresses[sb_count(checked_addresses) - 1] = malloc(MAX_LEN);
                            strcpy(checked_addresses[sb_count(checked_addresses) - 1], arr[i]);

                            add_bag(arr[i]);
                        }
                    }
                }
            }
        }
    }

    printf("%i\n", sb_count(checked_addresses));

    for (int i = 0; i < sb_count(checked_addresses); i++) {
        free(checked_addresses[i]);
    }
    for (int i = 0; i < sb_count(possible_bags); i++) {
        free(possible_bags[i]);
    }
    for (int i = 0; i < sb_count(arr); i++) {
        free(arr[i]);
    }
    sb_free(checked_addresses);
    sb_free(possible_bags);
    sb_free(arr);
    fclose(input);
    return 0;
}
