#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <stdbool.h>
#include <string.h>
#include "sh.h"

bool fileExists(char *filename) {
  struct stat buffer;
  return (stat (filename, &buffer) == 0);
}

int main(int argc, char const *argv[]) {
    if (argc > 1) {
        // hard coded commands
        if (strcmp(argv[1], "--help") == 0) {
            printf("%s\n", helpDocs);
            return 0;
        }

        // run a script file
        printf("Error: Running script files through sh command is not current supported.\nPlease use GNU sh or BASH instead\n");
        return 0;
    }

    char currentPathHead[256] = "./";
    while (true) {
        char command[256] = "";
        char commandArgs[256] = "";
        bool commandFound = false;

        printf("sh-%s%s", version, prompt);
        scanf("%s%s", &command, &commandArgs);

        // cd command
        if (strcmp(command, "cd") == 0) {
            strcpy(currentPathHead, commandArgs);
            commandFound = true;
        }

        // search through current directory
        char *currentDirectoryCommand = strcat(currentPathHead, command);
        if (fileExists(currentDirectoryCommand) && !commandFound) {
            system(command);
            commandFound = true;
        }

        if (!commandFound) {
            // search through all paths for a file which matches the command
            for (int i = 0; i < sizeof(paths); i++) {
                char *constructedCommand = strcat(paths[i], command);
                if (fileExists(constructedCommand) && !commandFound) {
                    system(constructedCommand);
                    commandFound = true;
                }
            }
        }

        if (!commandFound) {
            printf("sh: command not found: %s\n", command);
        }
    }

    return 0;
}
