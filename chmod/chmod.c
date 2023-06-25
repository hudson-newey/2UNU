#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "chmod.h"

int main(int argc, const char *argv[]) {
    if (argc < 2) {
        printf("chmod: missing operand\nTry 'chmod --help' for more information.\n");
        return 1;
    }

    if (strcmp(argv[1], "--version") == 0) {
        printf("%s\n", version);
        return 0;
    } else if (strcmp(argv[1], "--help") == 0) {
        printf("%s\n", helpDocs);
        return 0;
    }

    if (argv < 4) {
        printf("chmod: missing operand\nTry 'chmod --help' for more information.\n");
        return 1;
    }

    char *mode = argv[2];
    const char *filePath = argv[3];

    chmod(filePath, mode);

    return 0;
}
