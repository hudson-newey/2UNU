#include <stdio.h>
#include <string.h>
#include "printenv.h"

int main(int argc, const char *argv[], char *envp[]) {
    if (argc > 1) {
        if (strcmp(argv[1], "--version") == 0) {
            printf("%s\n", version);
            return 0;
        } else if (strcmp(argv[1], "--help") == 0) {
            printf("%s\n", helpDocs);
            return 0;
        }
        return 1;
    }

    for (int i = 0; envp[i] != NULL; i++) {
        printf("%s\n", envp[i]);
    }

    return 0;
}
