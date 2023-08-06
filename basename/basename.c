#include <stdio.h>
#include <string.h>
#include "basename.h"

void printBaseName(const char *filePath) {
    const char *fileName;

    fileName = strrchr(filePath, '/');

    if (fileName == NULL) {
        fileName = filePath;
    } else {
        fileName++;
    }

    printf("%s\n", fileName);
}

int main(int argc, const char *argv[]) {
    if (argc < 2) {
        printf("basename: missing operand\nTry 'basename --help' for more information.\n");
        return 1;
    }

    if (strcmp(argv[1], "--version") == 0) {
        printf("%s\n", version);
        return 0;
    } else if (strcmp(argv[1], "--help") == 0) {
        printf("%s\n", helpDocs);
        return 0;
    }

    const char *filePath = argv[1];
    printBaseName(filePath);

    return 0;
}
