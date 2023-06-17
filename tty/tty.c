#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h>
#include "tty.h"

int main(int argc, char const *argv[]) {
    bool isSilent = false;

    if (argc > 1) {
        if (
            strcmp(argv[1], "-s") == 0 ||
            strcmp(argv[1], "--silent") == 0 ||
            strcmp(argv[1], "--quiet") == 0
        ) {
            isSilent = true;
        }

        if (strcmp(argv[1], "--version") == 0) {
            printf("%s\n", version);
            return 0;
        }

        if (strcmp(argv[1], "--help") == 0) {
            printf("%s\n", helpDocs);
            return 0;
        }
    }

    if (!isSilent) {
        printf("%s\n", ttyname(fileno(stdout)));
    }

    if (isatty(fileno(stdout)) == 1) {
        return 0;
    } else {
        return 1;
    }
}
