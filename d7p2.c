#include <stdio.h>
#include <string.h>
#include "stretchy_buffer.h"

#define MAX_LEN 256

// stb stretchy_buffer resizable array
char **arr = NULL;
int total_bags = 0;

struct needed_bag {
    char style[32];
    int count;
};

struct needed_bag *add_bag(char *string) {
    struct needed_bag *bags = NULL;
    char **items = NULL;
    char *ptr = strtok(string, " ");
    for (int i = 0; ptr != NULL; i++) {
        sb_add(items, 1);
        items[sb_count(items) - 1] = malloc(32);
        strcpy(items[sb_count(items) - 1], ptr);
        ptr = strtok(NULL, " ");
    }

    if (strcmp(items[4], "no") == 0) {
        return NULL;
    }
    for (int i = 4; i < sb_count(items); i++) {        
        sb_add(bags, 1);
        int current = sb_count(bags) - 1;
        bags[current].count = atoi(items[i++]);
        strcpy(bags[current].style, items[i++]);
        strcat(bags[current].style, " ");
        strcat(bags[current].style, items[i++]);
    }

    return bags;
}

void check_bags(char *bag, int prev_product) {
    printf("%s: %i\n", bag, total_bags);
    struct needed_bag *current_bag = NULL;
    if (total_bags == 0) {
        for (int i = 0; i < sb_count(arr); i++) {
            char temp[128] = { 0 };
            strcpy(temp, arr[i]);
            char *p = strstr(temp, bag);
            if (p != NULL && p == temp) {
                current_bag = add_bag(temp);
                for (int j = 0; j < sb_count(current_bag); j++) {
                    total_bags += current_bag[j].count;
                }
                int count = sb_count(current_bag);
                for (int j = 0; j < sb_count(current_bag); j++) {
                    check_bags(current_bag[j].style, current_bag[j].count);
                }
                break;
            }
        }
    } else {
        for (int i = 0; i < sb_count(arr); i++) {
            char temp[128] = { 0 };
            strcpy(temp, arr[i]);
            char *p = strstr(temp, bag);
            if (p != NULL && p == temp) {
                current_bag = add_bag(temp);

                for (int j = 0; j < sb_count(current_bag); j++) {
                    int product = prev_product * current_bag[j].count;
                    total_bags += product;

                    if (current_bag[j].count == 0) {
                        break;
                    }
                    
                    check_bags(current_bag[j].style, product);
                }
                break;
            }
        }
    }

    sb_free(current_bag);
}

int main() {
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

    // Puzzle Start
    char *my_bag = "shiny gold";

    for (int i = 0; i < sb_count(arr); i++) {
        char *p = strstr(arr[i], my_bag);
        if (p != NULL && p == arr[i]) {
            check_bags(my_bag, 0);
            printf("%i\n", total_bags);
            break;
        }
    }

    for (int i = 0; i < sb_count(arr); i++) {
        free(arr[i]);
    }
    sb_free(arr);
    fclose(input);
    return 0;
}
