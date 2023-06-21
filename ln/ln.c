#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <stdbool.h>
#include "ln.h"

bool fileExists(char *filePath) {
  struct stat buffer;
  return stat(filePath, &buffer) == 0;
}

int main(int argc, const char *argv[]) {
    if (argc < 2) {
        printf("ln: missing file operand\nTry 'ln --help' for more information.\n");
        return 1;
    }

    if (argc < 3) {
        if (strcmp(argv[1], "--version") == 0) {
            printf("%s\n", version);
            return 0;
        } else if (strcmp(argv[1], "--help") == 0) {
            printf("%s\n", helpDocs);
            return 0;
        }

        char *filePathOne = argv[1];

        if (fileExists(filePathOne)) {
            printf("ln: failed to create hard link '%s': File exists\n", filePathOne);
            return 1;
        }

        printf("ln: failed to access '%s': No such file or directory\n", filePathOne);
        return 1;
    }

    char *filePathOne = argv[1];
    char *filePathTwo = argv[2];

    if (!fileExists(filePathOne)) {
        printf("ln: failed to access '%s': No such file or directory\n", filePathOne);
        return 1;
    }

    if (fileExists(filePathTwo)) {
        printf("ln: failed to create hard link '%s': File exists\n", filePathTwo);
        return 1;
    }

    symlink(filePathOne, filePathTwo);

    return 0;
}
