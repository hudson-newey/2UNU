#include <stdio.h>
#include <string.h>
#include "logname.h"
#define MAX_USERID_LENGTH 32

int main(int argc, const char *argv[]) {
    if (argc > 1) {
        if (strcmp(argv[1], "--version") == 0) {
            printf("%s\n", version);
            return 0;
        } else if (strcmp(argv[1], "--help") == 0) {
            printf("%s\n", helpDocs);
            return 0;
        }
    }

    char username[MAX_USERID_LENGTH];
    cuserid(username);

    printf("%s\n", username);

    return 0;
}
