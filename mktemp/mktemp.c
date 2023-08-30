#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <sys/stat.h>
#include "mktemp.h"

bool fileExists(char *filePath)
{
    struct stat buffer;
    return stat(filePath, &buffer) == 0;
}

void writeToFile(const char *filePath, char *content)
{
    FILE *fp = fopen(filePath, "w");

    fflush(stdin);
    fputs(content, fp);

    fclose(fp);
}

char generateRandomChar()
{
    const char charset[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    int index = rand() % (sizeof(charset) - 1);
    return charset[index];
}

char *tempFileName()
{
    bool tempFileExists = false;
    int prefixLength = sizeof(TEMP_FILE_NAME_PREFIX);

    int fileLength = TEMP_FILE_NAME_LENGTH + prefixLength;

    char *tempName = (char *)malloc(fileLength + sizeof(char));
    strcpy(tempName, TEMP_FILE_NAME_PREFIX);

    do
    {
        for (int i = prefixLength - 1; i < fileLength; i++)
        {
            char c = generateRandomChar();
            tempName[i] = c;
        }
        tempName[TEMP_FILE_NAME_LENGTH + prefixLength] = '\0';

        if (fileExists(tempName))
        {
            tempFileExists = true;
            strcpy(tempName, TEMP_FILE_NAME_PREFIX);
        }
        else
        {
            tempFileExists = false;
        }

    } while (tempFileExists);

    return tempName;
}

int createTempFile()
{
    const char *filePath = tempFileName();

    printf("%s\n", filePath);
    writeToFile(filePath, "");

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
    }

    return createTempFile();
}
