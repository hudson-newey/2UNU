#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cp.h"

char* readFile(const char *filePath) {
    char c;
    int i = 0;
    FILE *fp = fopen(filePath, "r");

    if (fp == NULL) {
        return NULL;
    }

    // Determine the size of the file
    fseek(fp, 0, SEEK_END);
    long fileSize = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    // Allocate memory for the output array
    char* output = (char*) malloc(fileSize + 1);

    // Read the contents of the file into the output array
    while ((c = getc(fp)) != EOF) {
        output[i++] = c;
    }
    output[i] = '\0';

    fclose(fp);

    return output;
}

void writeToFile(const char *filePath, char *content) {
    FILE *fp = fopen(filePath, "w");

    fflush(stdin);
    fputs(content,fp);

    fclose(fp);
}

int main(int argc, char const *argv[]) {
    if (argc < 2) {
        printf("cp: missing file operand\nTry 'cp --help' for more information.\n");
        return 1;
    }

    if (strcmp(argv[1], "--version") == 0) {
        printf("%s\n", version);
        return 0;
    } else if (strcmp(argv[1], "--help") == 0) {
        printf("%s\n", helpDocs);
        return 0;
    }

    if (argc < 3) {
        printf("cp: missing destination file operand after '%s'\nTry 'cp --help' for more information.\n", argv[1]);
        return 1;
    }

    const char *srcPath = argv[1];
    const char *destPath = argv[2];

    char *srcContent = readFile(srcPath);
    writeToFile(destPath, srcContent);

    return 0;
}
