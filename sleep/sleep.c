#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "sleep.h"

int main(int argc, const char *argv[]) {
    if (argc < 2) {
        printf(
            "sleep: missing operand\n"
            "Try 'sleep --help' for more information.\n"
        );
        return 1;
    }

    if (strcmp(argv[1], "--version") == 0) {
        printf("%s\n", version);
        return 0;
    } else if (strcmp(argv[1], "--help") == 0) {
        printf("%s\n", helpDocs);
        return 0;
    }

    double sleepDuration = atoi(argv[1]);
    sleep(sleepDuration);

    return 0;
}
