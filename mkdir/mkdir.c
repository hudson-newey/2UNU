#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>
#include <errno.h>
#include "mkdir.h"

int main(int argc, const char *argv[]) {
    if (argc < 2) {
        printf("mkdir: missing operand\nTry 'mkdir --help' for more information.\n");
        return 1;
    }

    if (strcmp(argv[1], "--version") == 0) {
        printf("%s\n", version);
        return 0;
    } else if(strcmp(argv[1], "--help") == 0) {
        printf("%s\n", helpDocs);
        return 0;
    }

    char *pathToCreate = argv[1];

    DIR* dir = opendir(pathToCreate);
    if (dir) {
        printf("mkdir: cannot create directory '%s': File exists\n", pathToCreate);
        closedir(dir);
        return 1;
    } else if (ENOENT == errno) {
        // here the path does not exist
        mkdir(pathToCreate, 0700);
        return 0;
    }

    return 1;
}
