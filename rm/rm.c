#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "rm.h"

int main(int argc, char const *argv[]) {
    if (argc < 2) {
        printf("rm: missing operand\nTry 'rm --help' for more information.\n");
        return 1;
    }

    // check for special arguments
    if (strcmp(argv[1], "--version") == 0) {
        printf("%s\n", version);
        return 0;
    } else if (strcmp(argv[1], "--help") == 0) {
        printf("%s\n", helpDocs);
        return 0;
    }

    const char *path = argv[1];
    unlink(path);

    return 0;
}
