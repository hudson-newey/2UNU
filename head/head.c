#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <sys/stat.h>
#include "head.h"

bool fileExists(char *filename)
{
    struct stat buffer;
    return (stat(filename, &buffer) == 0);
}

void fileHead(const char *filePath, int lines)
{
    char c;
    FILE *file = fopen(filePath, "r");

    int i = 0;
    while ((c = getc(file)) != EOF && i < lines)
    {
        printf("%c", c);

        if (c == '\n')
        {
            i++;
        }
    }

    fclose(file);
}

int main(int argc, const char *argv[])
{
    if (argc < 2)
    {
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

    const char *filePath = argv[1];
    int n = 10;

    if (!fileExists(filePath))
    {
        printf("head: cannot open '%s' for reading: No such file or directory\n", filePath);
        return 1;
    }

    fileHead(filePath, n);

    return 0;
}
