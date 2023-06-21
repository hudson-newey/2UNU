#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "cmp.h"

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("cmp: missing operand after 'cmp'\ncmp: Try 'cmp --help' for more information.\n");
        return 2;
    }

    if (strcmp(argv[1], "--version") == 0) {
        printf("%s\n", version);
        return 0;
    } else if (strcmp(argv[1], "--help") == 0) {
        printf("%s\n", helpDocs);
        return 0;
    }

    // if a second file is not specified, compare the first file to stdin
    if (argc < 3) {
        char *fileOne = argv[1];

        FILE *file;
        file = fopen(fileOne, "r");

        unsigned char buffer[8];
        bool foundDifference = false;
        while(*buffer != EOF) {
            scanf("%c", &buffer);
            if (buffer[0] == EOF) {
                break;
            } else if (buffer[0] != (unsigned char)fgetc(file)) {
                foundDifference = true;
            }
        }

        // since false is actually just a macro for 0 and true is just a macro for 1
        // we can actually just return this boolean value
        return foundDifference;
    }

    // compare two files by path
    char *filePathOne = argv[1];
    char *filePathTwo = argv[2];
    FILE *fileOne, *fileTwo;

    fileOne = fopen(filePathOne, "r");
    fileTwo = fopen(filePathTwo, "r");

    unsigned int byte = 0;
    unsigned int line = 1;

    char bufferOne, bufferTwo;
    while((bufferOne = fgetc(fileOne)) != EOF && (bufferTwo = fgetc(fileTwo)) != EOF) {
        byte++;

        if (bufferOne == newline && bufferTwo == newline) {
            line++;
            byte = 0;
            continue;
        }

        if (bufferOne != bufferTwo) {
            printf("%s %s differ: byte %d, line %d\n", filePathOne, filePathTwo, byte, line);
            return 1;
        }
    }

    fclose(fileOne);
    fclose(fileTwo);

    return 0;
}
