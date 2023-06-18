#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <sys/stat.h>
#include "touch.h"

char* readFile(char *filePath) {
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

void writeToFile(char *filePath, char *content) {
    FILE *fp = fopen(filePath, "w");

    fflush(stdin);
    fputs(content,fp);

    fclose(fp);
}

bool fileExists(char *filePath) {
  struct stat buffer;
  return stat(filePath, &buffer) == 0;
}

int main(int argc, const char *argv[]) {
    if (argc < 2) {
        printf("touch: missing file operand\nTry 'touch --help' for more information.\n");
        return 1;
    }

    if (strcmp(argv[1], "--version") == 0) {
        printf("%s\n", version);
        return 0;
    } else if (strcmp(argv[1], "--help") == 0) {
        printf("%s\n", helpDocs);
        return 0;
    }

    char *filePath = argv[1];

    // if the file exists, update the modified time
    // otherwise, create an empty file
    if (fileExists(filePath)) {
        char *fileContents = readFile(filePath);
        writeToFile(filePath, fileContents);
    } else {
        writeToFile(filePath, "");
    }
}
