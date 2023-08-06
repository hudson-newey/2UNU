#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <sys/stat.h>
#include "history.h"

bool fileExists(char *filePath) {
  struct stat buffer;
  return stat(filePath, &buffer) == 0;
}

void printFile(char *fileName) {
    char c;
    FILE *file = fopen(fileName, "r");

    unsigned int lineNumber = 1;
    bool printLineNumber = true;
    
    while ((c = getc(file)) != EOF) {
        if (printLineNumber) {
            printf("%d: ", lineNumber);
            printLineNumber = false;
        }

        printf("%c", c);

        if (c == '\n') {
            lineNumber++;
            printLineNumber = true;
        }
    }

    fclose(file);

    printf("\n");
}

int printHistory() {
    char *knownHistoryFiles[] = {
        "/home/grathium/.bash_history",
        "/home/grathium/.history",
        "/home/grathium/.sh_history",
    };

    for (int i = 0; i < 5; i++) {
        if (fileExists(knownHistoryFiles[i])) {
            printFile(knownHistoryFiles[i]);
        }
    }

    return 0;
}

// this command is usually not POSIX compliant
// however, since I'm trying recreate all the commands with POSIX compliance, I want to create the history command
// the history command will scan for history files in the home directory and print them all out
int main(int argc, const char *argv[]) {
    if (argc > 1) {
        if (strcmp(argv[1], "--version") == 0) {
            printf("%s\n", version);
            return 0;
        } else if (strcmp(argv[1], "--help") == 0) {
            printf("%s\n", helpDocs);
            return 0;
        }

        return 1;
    }

    return printHistory();
} 
