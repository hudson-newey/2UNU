#include <stdio.h>
#include <string.h>
#include "mount.h"

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

int mountDrive(const char *filePath)
{
    printf("ERROR: not currently supported\n");
    return 0;
}

// the mount command reads out the file at /proc/mounts
// therefore, I replicate this behaviour
int printMountedDrives()
{
    printFile(MOUNT_INFO_PATH);
    return 0;
}

int main(int argc, const char *argv[])
{
    if (argc < 2) {
        return printMountedDrives();
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
    return mountDrive(filePath);
}
