#include <stdio.h>
#include <string.h>
#include "uname.h"

int main(int argc, char const *argv[]) {
    if (argc > 1) {
        if (strcmp(argv[1], "--version") == 0) {
            printf("%s\n", version);
            return 0;
        } else if (strcmp(argv[1], "--help") == 0) {
            printf("%s\n", helpDocs);
            return 0;
        }
    }

    // TODO: I need to make this better
    printf("Linux\n");

    return 0;
}
