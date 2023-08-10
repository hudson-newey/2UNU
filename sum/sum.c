#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sum.h"


#define BLOCK_SIZE 1024
#define INPUT_BUFFER 2048
#define IO_STREAM_TEMP_FILE "/tmp/temp.txt"

int countFileBlocks(const char *filePath) {
    FILE *file = fopen(filePath, "rb");

    if (file == NULL) {
        perror("Error opening file");
        return -1;
    }

    fseek(file, 0, SEEK_END);
    long fileSize = ftell(file);
    int blockCount = (int)((fileSize + BLOCK_SIZE - 1) / BLOCK_SIZE);

    fclose(file);

    return blockCount;
}

int checkSumFromFile(const char *filePath) {
    FILE *file = fopen(filePath, "rb");

    if (file == NULL) {
        perror("Error opening file");
        return 0;
    }

    int checksum = 0;
    unsigned char buffer[BLOCK_SIZE];
    size_t bytesRead;

    while ((bytesRead = fread(buffer, 1, sizeof(buffer), file)) > 0) {
        size_t i;
        for (i = 0; i < bytesRead; i++) {
            checksum = (checksum >> 1) + ((checksum & 1) << 15);
            checksum += buffer[i];
            checksum &= 0xffff;
        }
    }

    fclose(file);

    return (int)checksum;
}

void writeToFile(const char *filePath, char fileContents[][INPUT_BUFFER]) {
    FILE *file = fopen(filePath, "w");

    if (file == NULL) {
        printf("Error opening file: %s\n", filePath);
        exit(1);
    }

    for (int i = 0; fileContents[i][0] != '\0'; i++) {
        fputs(fileContents[i], file);
    }

    fclose(file);
}

void deleteFile(const char *filePath) {
    if (remove(filePath) != 0) {
        printf("Error deleting file: %s\n", filePath);
    }
}

int printCheckSum(const char *filePath, int value) {
    int fileBlockSize = countFileBlocks(filePath);

    printf("%d\t  %d %s\n", value, fileBlockSize, filePath);
    return 0;
}

int readFromIoStream() {
    char contents[INPUT_BUFFER][INPUT_BUFFER];
    char input[INPUT_BUFFER];

    char *input_ptr = input;
    while (*input_ptr != EOF) {
        input_ptr = fgets(input_ptr, INPUT_BUFFER, stdin);
    }
    const char *tempFilePath = IO_STREAM_TEMP_FILE;

    writeToFile(tempFilePath, contents);

    int calculatedSum = checkSumFromFile(tempFilePath);
    int returnValue = printCheckSum(tempFilePath, calculatedSum);

    deleteFile(tempFilePath);

    return returnValue;
}

int main(int argc, const char *argv[]) {
    if (argc > 1) {
        if (strcmp(argv[1], "--version") == 0) {
            printf("%s\n", version);
            return 0;
        } else if (strcmp(argv[1], "--help") == 0) {
            printf("%s\n", helpDocs);
            return 0;
        }
    } else {
        return readFromIoStream();
    }

    const char *filePath = argv[1];
    int calculatedSum = checkSumFromFile(filePath);
    return printCheckSum(filePath, calculatedSum);
}
