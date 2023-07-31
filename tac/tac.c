#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <sys/stat.h>
#include "tac.h"

int printError(int errorCode, char *message) {
    printf("tac: %s\n", message);
    return errorCode;
}

bool fileExists(char *filePath) {
  struct stat buffer;
  return stat(filePath, &buffer) == 0;
}

// uses STDIN stream as input
// this is mostly used in bash pipes
int fromStdIn() {
    return 0;
}

int fromFile(char *filePath) {
    if (!fileExists(filePath)) {
        char errorMessage[256];
        snprintf(errorMessage, sizeof(errorMessage), "cannot open '%s' for reading: No such file or directory", filePath);
        return printError(1, errorMessage);
    }

    FILE *file = fopen(filePath, "r");

    fseek(file, 0, SEEK_END);

    int lineCount = 0;
    long currentPosition = ftell(file);

    while (currentPosition > 0) {
        if (fgetc(file) == '\n') {
            lineCount++;
        }
        fseek(file, --currentPosition, SEEK_SET);
    }

    // print each line from the file starting from the bottom and going to the top
    for (int i = lineCount; i >= 0; i--) {
        fseek(file, 0, SEEK_SET);

        int currentLine = 0;
        char line[256];

        while (currentLine < i) {
            fgets(line, sizeof(line), file);
            currentLine++;
        }

        printf("%s", line);
    }

    return 0;
}

int main(int argc, const char *argv[]) {
    if (argc == 1) {
        return fromStdIn();
    }

    if (strcmp(argv[1], "--version") == 0) {
        printf("%s\n", version);
        return 0;
    } else if (strcmp(argv[1], "--help") == 0) {
        printf("%s\n", helpDocs);
        return 0;
    }

    const char *filePath = argv[1];

    return fromFile(filePath);
}
