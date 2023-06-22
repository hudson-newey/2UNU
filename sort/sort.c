#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <stdbool.h>
#include "sort.h"

#define BUFFER_LENGTH 2056

void printFileContent(char **fileContent) {
    for (unsigned int i = 0; fileContent[i] != NULL; i++) {
        // there is no need to include the newline character here since each line
        // should be at a different memory offset
        printf("%s", fileContent[i]);
    }
}

// sort lines of the file using bubble sort
char** sortFileContent(char **fileContent) {
    int numLines = 0;
    while (fileContent[numLines] != NULL) {
        numLines++;
    }

    for (int i = 0; i < numLines - 1; i++) {
        for (int j = 0; j < numLines - i - 1; j++) {
            if (strcmp(fileContent[j], fileContent[j+1]) > 0) {
                char *temp = fileContent[j];
                fileContent[j] = fileContent[j+1];
                fileContent[j+1] = temp;
            }
        }
    }

    return fileContent;
}

char** readFileLines(char *fileName) {
    FILE* filePointer;
    char readBuffer[BUFFER_LENGTH];
    char **fileLines = NULL;
    int numLines = 0;

    filePointer = fopen(fileName, "r");
    if (filePointer == NULL) {
        printf("Error: could not open file %s\n", fileName);
        return NULL;
    }

    while(fgets(readBuffer, BUFFER_LENGTH, filePointer)) {
        numLines++;
        fileLines = realloc(fileLines, numLines * sizeof(char*));
        fileLines[numLines-1] = malloc(strlen(readBuffer)+1);
        strcpy(fileLines[numLines-1], readBuffer);
    }

    fclose(filePointer);

    return fileLines;
}

bool fileExists(char *filePath) {
  struct stat buffer;
  return stat(filePath, &buffer) == 0;
}

int main(int argc, char *argv[]) {
    if (argc > 1) {
        if (strcmp(argv[1], "--version") == 0) {
            printf("%s\n", version);
            return 0;
        } else if (strcmp(argv[1], "--help") == 0) {
            printf("%s\n", helpDocs);
            return 0;
        }

        char *filePath = argv[1];
        if (!fileExists(filePath)) {
            printf("sort: cannot read: '%s': No such file or directory\n", filePath);
            return 2;
        }

        char **fileContent = readFileLines(filePath);
        char **sortedFileContent = sortFileContent(fileContent);

        printFileContent(sortedFileContent);
    } else {
        // read from stdin
        // this is most widely used in shell pipes
        char fileContent[BUFFER_LENGTH][BUFFER_LENGTH];
        char inputBuffer[BUFFER_LENGTH];
        unsigned int i = 0;

        while(*inputBuffer != EOF) {
            fgets(inputBuffer, BUFFER_LENGTH, stdin);
            strcpy(fileContent[i], inputBuffer);
            i++;
        }

        char **sortedFileContent = sortFileContent(fileContent);

        printFileContent(sortedFileContent);
    }

    return 0;
}
