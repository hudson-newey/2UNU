#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <sys/stat.h>
#include <zlib.h>
#include "gzip.h"

#define BUFFER_SIZE 1024

bool fileExists(const char *filePath)
{
    struct stat buffer;
    return stat(filePath, &buffer) == 0;
}

void deleteFile(const char *filePath)
{
    if (fileExists(filePath))
    {
        unlink(filePath);
    }
}

int gzipFile(const char *filePath)
{
    char fileIn[1024];
    strcpy(fileIn, filePath);
    const char* outputFilePath = strcat(fileIn, FILE_EXTENSION);

    FILE* src = fopen(filePath, "rb");
    gzFile dst = gzopen(outputFilePath, "wb");

    char buffer[BUFFER_SIZE];
    int bytes_read;

    while ((bytes_read = fread(buffer, 1, sizeof(buffer), src)) > 0) {
        if (gzwrite(dst, buffer, bytes_read) != bytes_read) {
            perror("Error writing compressed data");
            gzclose(dst);
            fclose(src);
            return 1;
        }
    }

    fclose(src);
    gzclose(dst);

    deleteFile(filePath);

    return 0;
}

int main(int argc, const char *argv[])
{
    if (argc < 2)
    {
        printf("gzip: compressed data not written to a terminal. Use -f to force compression.\nFor help, type: gzip -h\n");
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

    const char* inputFilePath = argv[1];
    return gzipFile(inputFilePath);
}
