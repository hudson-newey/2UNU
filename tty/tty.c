#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h>
#include "tty.h"

bool isSilent(int argc, const char *argv[])
{
    if (argc == 1)
    {
        return false;
    }

    return strcmp(argv[1], SILENT_CLA_SHORT) == 0 ||
           strcmp(argv[1], SILENT_CLA_LONG) == 0 ||
           strcmp(argv[1], QUIET_CLA) == 0;
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

        if (strcmp(argv[1], "--help") == 0)
        {
            printf("%s\n", helpDocs);
            return 0;
        }

        if (!isSilent(argc, argv))
        {
            printf(EXTRA_OPERAND_MESSAGE, argv[1]);
            return 2;
        }
    }

    if (!isSilent(argc, argv))
    {
        printf("%s\n", ttyname(fileno(stdout)));
    }

    if (isatty(fileno(stdout)) == 1)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}
