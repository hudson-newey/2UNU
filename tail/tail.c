#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <sys/stat.h>
#include "tail.h"

void fileTail(char *filePath, int n) {
    FILE *file = fopen(filePath, "r");

    fseek(file, 0, SEEK_END);

    int lineCount = 0;
    long currentPosition = ftell(file);

    while (currentPosition > 0 && lineCount < n) {
        if (fgetc(file) == '\n') {
            lineCount++;
        }
        fseek(file, --currentPosition, SEEK_SET);
    }

    if (lineCount < n) {
        lineCount++;
    }

    fseek(file, currentPosition, SEEK_SET);
    int ch;
    while ((ch = fgetc(file)) != EOF) {
        putchar(ch);
    }
}

bool fileExists(char *filePath) {
  struct stat buffer;
  return stat(filePath, &buffer) == 0;
}

int main(int argc, const char *argv[]) {
    if (argc < 2) {
        return 1;
    }

    if (strcmp(argv[1], "--version") == 0) {
        printf("%s\n", version);
        return 0;
    } else if (strcmp(argv[1], "--help") == 0) {
        printf("%s\n", helpDocs);
        return 0;
    }

    const char* filePath = argv[1];
    int n = 10;

    if (!fileExists(filePath)) {
        printf("tail: cannot open '%s' for reading: No such file or directory\n", filePath);
        return 1;
    }

    fileTail(filePath, n);

    return 0;
}
