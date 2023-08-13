#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dircolors.h"

void printEnvironmentVariable(char *name)
{
    const char *value = getenv(name);

    if (value != NULL)
    {
        printf("%s='%s';\n", name, value);
    }
    else
    {
        printf("%s: Undefined variable.\n", name);
    }
}

int printDirColors()
{
    printEnvironmentVariable("LS_COLORS");
    printf("export LS_COLORS\n");
    return 0;
}

int main(int argc, char *argv[], char *envp[])
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

        const char *filename = argv[1];
        printf("dircolors: '%s': No such file or directory\n", filename);
        return 1;
    }

    return printDirColors();
}
