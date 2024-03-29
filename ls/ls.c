#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <stdbool.h>
#include <dirent.h>
#include "ls.h"

struct IOptions
{
    bool showHidden;
    bool longFormat;
};

void listDirectory(const char *path, struct IOptions *options)
{
    DIR *d;
    struct dirent *dir;
    d = opendir(path);

    while ((dir = readdir(d)) != NULL)
    {
        const char *name = dir->d_name;

        if (name[0] == '.' && options->showHidden == false)
            continue;

        printf("%s  ", dir->d_name);

        if (options->longFormat)
            printf("\n");
    }

    closedir(d);

    printf("\n");
}

bool isDirectory(const char *path)
{
    struct stat s = {0};
    return !stat(path, &s);
}

bool stringInArray(char* target, char* array[], size_t arraySize) {
    for (size_t i = 0; i < arraySize; i++) {
        if (strcmp(target, array[i]) == 0) {
            return true;
        }
    }
    return false;
}

int main(int argc, char const *argv[])
{
    struct IOptions defaultOptions = {false};

    // print out the current directory
    if (argc == 1)
    {
        listDirectory(".", &defaultOptions);
        return 0;
    }

    // check for special flags
    if (argc > 1)
    {
        if (strcmp(argv[1], "--help") == 0)
        {
            printf("%s\n", helpDocs);
            return 0;
        }

        if (strcmp(argv[1], "--version") == 0)
        {
            printf("%s\n", version);
            return 0;
        }

        // cla flags
        if (stringInArray(SHOW_HIDDEN_CLA, argv, argc)) {
            defaultOptions.showHidden = true;
        }
    }

    // assume that the cla 1 is a path
    const char *path = argv[1];
    if (isDirectory(path))
    {
        listDirectory(path, &defaultOptions);
    }
    else
    {
        printf("ls: cannot access '%s': No such file or directory\n", path);
        return 2;
    }

    return 0;
}
