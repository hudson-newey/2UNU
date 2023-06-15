#include "constants.h"
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>

void printCurrentPath(bool includeSymLinks) {
    char buff[FILENAME_MAX];

    // TODO: at the moment there isn't a difference between the two -L and -P flags
    // I need to find out exactly what they do and implement them
    if (includeSymLinks) {
        getcwd(buff, FILENAME_MAX);
    } else {
        getcwd(buff, FILENAME_MAX);
    }

    printf("%s\n", buff);
}

int main(int argc, char const *argv[]) {
    if (argc < 2) {
        printCurrentPath(argv);
        return 0;
    }

    // directory command line arguments
    if (!strcmp(argv[1], "-L") || !strcmp(argv[1], "--logical")) {
        printCurrentPath(true);
    }

    if (!strcmp(argv[1], "-P") || !strcmp(argv[1], "--physical")) {
        printCurrentPath(false);
    }

    // help command line arguments
    if (!strcmp(argv[1], versionCla)) {
        printf("%s\n", version);
        return 0;
    } else if (!strcmp(argv[1], helpDocsCla)) {
        printf("%s\n", helpDocs);
        return 0;
    }

    printf("Unknown Argument %s\n", argv[1]);
    return 1;
}
