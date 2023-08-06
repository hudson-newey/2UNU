#include <stdio.h>
#include <string.h>
#include "userdel.h"

int deleteUser(const char *username) {
    return 0;
}

int main(int argc, const char *argv[]) {
    if (argc < 2) {
        printf("%s\n", helpDocs);
        return 2;
    }

    if (strcmp(argv[1], "--version") == 0) {
        printf("%s\n", version);
        return 0;
    } else if (strcmp(argv[1], "--help") == 0) {
        printf("%s\n", helpDocs);
        return 0;
    }

    const char *username = argv[1];

    return deleteUser(username);
}
