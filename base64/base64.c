#include <openssl/bio.h>
#include <openssl/evp.h>

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>
#include "base64.h"

#define BUFFER_SIZE 1024
#define IO_STREAM_TEMP_FILE "/tmp/temp.txt"

bool fileExists(const char *filePath)
{
    struct stat buffer;
    return (stat(filePath, &buffer) == 0);
}

void writeToFile(char *filePath, char contents[][BUFFER_SIZE])
{
    FILE *filePointer = fopen(filePath, "w");
    if (filePointer == NULL)
    {
        printf("Error: could not open file %s\n", filePath);
        return;
    }

    for (unsigned int i = 0; contents[i][0] != '\0'; i++)
    {
        fprintf(filePointer, "%s", contents[i]);
    }

    fclose(filePointer);
}

void deleteFile(char *filePath)
{
    if (fileExists(filePath))
    {
        remove(filePath);
    }
    else
    {
        printf("Error: failed to delete temp file, file %s does not exist\n", filePath);
    }
}

char *readFile(const char *filePath)
{
    FILE *f = fopen(filePath, "rb");

    // f invalid? fseek() fail?
    if (f == NULL || fseek(f, 0, SEEK_END))
    {
        return NULL;
    }

    long length = ftell(f);
    rewind(f);
    // Did ftell() fail?  Is the length too long?
    if (length == -1 || (unsigned long)length >= SIZE_MAX)
    {
        return NULL;
    }

    // Convert from long to size_t
    size_t ulength = (size_t)length;
    char *buffer = malloc(ulength + 1);
    // Allocation failed? Read incomplete?
    if (buffer == NULL || fread(buffer, 1, ulength, f) != ulength)
    {
        free(buffer);
        return NULL;
    }
    buffer[ulength] = '\0'; // Now buffer points to a string

    return buffer;
}

char *Base64Encode(const char *message)
{
    BIO *bio, *b64;
    FILE *stream;

    int encodedSize = 4 * ceil((double)strlen(message) / 3);

    char *buffer = (char *)malloc(encodedSize + 1);

    stream = fmemopen(buffer, encodedSize + 1, "w");
    b64 = BIO_new(BIO_f_base64());
    bio = BIO_new_fp(stream, BIO_CLOSE);

    bio = BIO_push(b64, bio);

    BIO_set_flags(bio, BIO_FLAGS_BASE64_NO_NL);
    BIO_write(bio, message, strlen(message));

    BIO_flush(bio);
    fclose(stream);

    return buffer;
}

char *base64EncodeFile(const char *filePath)
{
    char *fileContents = readFile(filePath);

    printf("%s\n", fileContents);

    char *base64EncodeOutput = Base64Encode(fileContents);
    return base64EncodeOutput;
}

char *base64EncodeIoStream()
{
    char fileContent[BUFFER_SIZE][BUFFER_SIZE];
    char inputBuffer[BUFFER_SIZE];
    unsigned int i = 0;

    while (*inputBuffer != EOF)
    {
        fgets(inputBuffer, BUFFER_SIZE, stdin);
        strcpy(fileContent[i], inputBuffer);
        i++;
    }

    writeToFile(IO_STREAM_TEMP_FILE, fileContent);

    char *base64Output = base64EncodeFile(IO_STREAM_TEMP_FILE);
    deleteFile(IO_STREAM_TEMP_FILE);

    return base64Output;
}

// this program requires openssl and should be compiled with -lcrypto -lm gcc compiler flags
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
    else
    {
        char *base64Encoding = base64EncodeIoStream();
        printf("%s\n", base64Encoding);
        return 0;
    }

    const char *filePath = argv[1];
    char *base64Encoding = base64EncodeFile(filePath);
    printf("%s\n", base64Encoding);

    return 0;
}
