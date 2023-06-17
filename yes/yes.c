#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "yes.h"

void defaultPrint() {
    while (true) {
        printf("%s\n", DEFAULT_STRING);
    }
}

int main(int argc, char const *argv[]) {
    if (argc < 2) {
        defaultPrint();
    }

    if (strcmp(argv[1], "--version") == 0) {
        printf("%s\n", version);
        return 0;
    } else if (strcmp(argv[1], "--help") == 0) {
        printf("%s\n", helpDocs);
        return 0;
    }

    while (true) {
        for (int i = 1; i < argc; i++) {
            printf("%s", argv[i]);

            if (i < argc - 1) {
                printf(" ");
            }
        }

        printf("\n");
    }

    return 0;
}
