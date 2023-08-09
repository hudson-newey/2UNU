#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dirname.h"

int printDirPath(const char *path)
{
    // if the last character is a slash, remove it
    int pathLen = strlen(path);
    if (path[pathLen - 1] == '/')
    {
        char *newPath = malloc(pathLen);
        strncpy(newPath, path, pathLen - 1);
        newPath[pathLen - 1] = '\0';
        path = newPath;
    }

    // remove everything after the last slash
    char *lastSlash = strrchr(path, '/');
    if (lastSlash != NULL)
    {
        *lastSlash = '\0';
    }

    printf("%s\n", path);

    return 0;
}

int main(int argc, const char *argv[])
{
    if (argc < 2)
    {
        printf("dirname: missing operand\nTry 'dirname --help' for more information.\n");
        return 1;
    }

    if (strcmp(argv[1], "--version") == 0)
    {
        printf("%s\n", version);
        return 0;
    }
    else if (strcmp(argv[1], "--help") == 0)
    {
        printf("%s\n", helpDocs);
        return 0;
    }

    const char *path = argv[1];

    return printDirPath(path);
}
