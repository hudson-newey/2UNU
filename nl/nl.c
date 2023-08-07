#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <sys/stat.h>
#include "nl.h"

bool fileExists(char *filename)
{
    struct stat buffer;
    return (stat(filename, &buffer) == 0);
}

int readFromStdIo()
{
    unsigned int i = 1;

    while (true)
    {
        char line[1024];
        char *result = fgets(line, 1024, stdin);

        if (result == NULL && result == EOF)
        {
            break;
        }

        printf("\t%d  %s", i, line);

        i++;
    }

    return 0;
}

int readFromFile(const char *filePath)
{
    if (fileExists(filePath)) {
        const char *printingFormat = "    %d  ";

        char c;
        bool previousWasNl = true;
        FILE *file = fopen(filePath, "r");

        unsigned int i = 1;
        while ((c = getc(file)) != EOF)
        {
            if (previousWasNl && c != '\n')
            {
                printf(printingFormat, i);
                i++;
            }

            printf("%c", c);

            previousWasNl = c == '\n';
        }

        fclose(file);

    } else {
        printf("nl: '%s': No such file or directory\n", filePath);
        return 1;
    }

    return 0;
}

int main(int argc, const char *argv[])
{
    if (argc > 1)
    {
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
        return readFromFile(filePath);
    }

    return readFromStdIo();
}
