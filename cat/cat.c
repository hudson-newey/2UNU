#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <sys/stat.h>
#include "cat.h"

void printFile(const char *filePath)
{
    char c;
    FILE *file = fopen(filePath, "r");

    while ((c = getc(file)) != EOF)
    {
        printf("%c", c);
    }

    fclose(file);
}

bool fileExists(const char *filePath)
{
    struct stat buffer;
    return stat(filePath, &buffer) == 0;
}

int main(int argc, const char *argv[])
{
    if (argc < 2)
    {
        while (true)
        {
            char c = getchar();
            if (c == EOF)
            {
                break;
            }
            printf("%c", c);
        }
        return 0;
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

    for (int i = 1; i < argc; i++)
    {
        const char *filePath = argv[i];
        if (!fileExists(filePath))
        {
            printf("cat: %s: No such file or directory\n", filePath);
            return 1;
        }

        printFile(filePath);
    }
}
