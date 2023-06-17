#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <stdbool.h>
#include <dirent.h>
#include "ls.h"

void listDirectory(char *path) {
    DIR *d;
    struct dirent *dir;
    d = opendir(".");
    while ((dir = readdir(d)) != NULL) {
        printf("%s\n", dir->d_name);
    }
    closedir(d);
}

bool isDirectory(char *path) {
    struct stat s = {0};
    return !stat(path, &s);
}

int main(int argc, char const *argv[]) {
    // print out the current directory
    if (argc == 1) {
        listDirectory(".");
        return 0;
    }

    // check for special flags
    if (argc > 1) {
        if (strcmp(argv[1], "--help") == 0) {
            printf("%s\n", helpDocs);
            return 0;
        }

        if (strcmp(argv[1], "--version") == 0) {
            printf("%s\n", version);
            return 0;
        }
    }

    // assume that the cla 1 is a path
    char *path = argv[1];
    if (isDirectory(path)) {
        printf("here");
    } else {
        printf("ls: cannot access '%s': No such file or directory\n", path);
        return 2;
    }

    return 0;
}
