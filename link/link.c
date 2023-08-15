#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <stdbool.h>
#include "link.h"

bool fileExists(const char *filePath) {
  struct stat buffer;
  return stat(filePath, &buffer) == 0;
}

int createHardLink(const char *sourcePath, const char *destinationPath) {
    if (!fileExists(sourcePath)) {
        printf("link: cannot create link '%s' to '%s': No such file or directory\n", destinationPath, sourcePath);
        return 1;
    }

    if (fileExists(destinationPath)) {
        printf("link: cannot create link '%s' to '%s': File exists\n", destinationPath, sourcePath);
        return 1;
    }

    return link(sourcePath, destinationPath);
}

int main(int argc, const char *argv[]) {
    if (argc < 2) {
        printf("link: missing file operand\nTry 'ln --help' for more information.\n");
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

        const char *sourcePath = argv[1];
        printf("link: missing operand after '%s'\nTry 'link --help' for more information.\n", sourcePath);
        return 1;
    }

    const char *sourcePath = argv[1];
    const char *destinationPath = argv[2];
    return createHardLink(sourcePath, destinationPath);
}
