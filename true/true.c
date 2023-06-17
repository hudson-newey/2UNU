#include <stdio.h>
#include <string.h>
#include "true.h"

int main(int argc, char const *argv[]) {
    // the GNU cli doesn't actually implement --help and --version in their implementation
    // however, it specifies that it should in the docs
    // I believe this to be a bug in the GNU implementation, and therefore, I have fixed it in my implementation
    if (argc > 1) {
        if (strcmp(argv[1], "--help") == 0) {
            printf("%s\n", helpDocs);
            return 0;
        } else if (strcmp(argv[1], "--version") == 0) {
            printf("%s\n", version);
            return 0;
        }
    }

    return EXIT_CODE;
}
