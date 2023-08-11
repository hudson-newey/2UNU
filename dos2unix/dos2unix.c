#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <sys/stat.h>
#include "dos2unix.h"

#define BUFFER_SIZE 2056

bool fileExists(const char *filePath)
{
    struct stat buffer;
    return stat(filePath, &buffer) == 0;
}

// read the file, and replace all \r\n with \n
// then write back to the same file with all \r\n replaced with \n
int convertFile(const char *filePath)
{
    if (!fileExists(filePath))
    {
        printf(
            "dos2unix: '%s': No such file or directory\ndos2unix: Skipping '%s', not a regular file.\n",
            filePath,
            filePath
        );
        return 2;
    }

    printf("dos2unix: converting file '%s' to Unix format...\n", filePath);

    FILE *file = fopen(filePath, "r");
    if (file == NULL)
    {
        printf("Error: could not open file %s\n", filePath);
        return 1;
    }

    fseek(file, 0, SEEK_END);
    long fileSize = ftell(file);
    fseek(file, 0, SEEK_SET);

    char *fileContent = (char *)malloc(fileSize);
    fread(fileContent, 1, fileSize, file);
    fclose(file);

    char *pos = strstr(fileContent, "\r");
    while (pos != NULL) {
        // remove pos from fileContent
        memmove(pos, pos + 1, strlen(pos));
        fileSize--;
        pos = strstr(pos + 1, "\r");
    }

    file = fopen(filePath, "wb");
    fwrite(fileContent, 1, fileSize, file);
    fclose(file);

    free(fileContent);

    return 0;
}

int main(int argc, const char *argv[])
{
    if (argc < 2)
    {
        // TODO: get this working
        printf("Error: reading from IO stream is not currently supported\n");
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
    return convertFile(filePath);
}
