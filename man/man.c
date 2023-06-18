#include <stdio.h>
#include <string.h>
#include "man.h"

int main(int argc, const char *argv[]) {
    if (argc < 2) {
        printf("What manual page do you want?\nFor example, try 'man man'.\n");
        return 1;
    }

    if (strcmp(argv[1], "--version") == 0) {
        printf("%s\n", version);
        return 0;
    } else if (strcmp(argv[1], "--help") == 0) {
        printf("%s\n", helpDocs);
        return 0;
    }

    const char *program = argv[1];

    printf("this command is currently incomplete, please check back later...\n");

    return 0;
}
