#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "useradd.h"

bool userExists(const char *username) {
    return false;
}

int addUser(const char *username) {
    if (userExists(username)) {
        // the GNU implementation doesn't return an error code
        // we should probably consider returning an error code here
        return 0;
    }

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

    return addUser(username);
}
