#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arch.h"

void printFile(char *fileName) {
    char c;
    FILE *file = fopen(fileName, "r");

    while ((c = getc(file)) != EOF) {
        printf("%c", c);
    }

    fclose(file);
}

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

    // TODO: I should probably parse the /proc/cpuinfo file to keep it in spec with GNU
    printFile("/proc/cpuinfo");

    return 0;
}
