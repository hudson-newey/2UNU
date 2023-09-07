#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include "lscpu.h"

void printFile(char *filePath)
{
    char c;
    FILE *file = fopen(filePath, "r");

    while ((c = getc(file)) != EOF)
    {
        printf("%c", c);
    }

    fclose(file);
}

int printCpuIoInformation()
{
    printFile(CPU_INFO_LOCATION);
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

        printf("lscpu: bad usage\nTry 'lscpu --help' for more information.\n");
        return 1;
    }

    return printCpuIoInformation();
}
