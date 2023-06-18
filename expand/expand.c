#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "expand.h"

#define MAX_INPUT_LENGTH 256

void printExpanded(char *string) {
    char newString[strlen(string) * 8 + 1];
    int newIndex = 0;
    for (int i = 0; i < strlen(string); i++) {
        if (string[i] == '\t') {
            for (int j = 0; j < 8; j++) {
                newString[newIndex++] = ' ';
            }
        } else {
            newString[newIndex++] = string[i];
        }
    }
    newString[newIndex] = '\0';
    strcpy(string, newString);

    printf("%s", string);
}

int main(int argc, const char *argv[]) {
    if (argc > 1) {
        if (strcmp(argv[1], "--version") == 0) {
            printf("%s\n", version);
            return 0;
        } else if (strcmp(argv[1], "--help") == 0) {
            printf("%s\n", helpDocs);
            return 0;
        }
    }

    // if CLA 1 is used, replace all tabs with spaces
    // otherwise, get user input and replace tabs with spaces
    if (argc < 2) {
        while(true) {
            char input[MAX_INPUT_LENGTH];
            fgets(input, MAX_INPUT_LENGTH, stdin);
            printExpanded(input);
        }
    }

    for (int i = 1; i < argc; i++) {
        printExpanded(argv[i]);

        if (i < argc - 1) {
            printf(" ");
        }
    }

    return 0;
}
