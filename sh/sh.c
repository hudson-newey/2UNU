#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <stdbool.h>
#include <string.h>
#include "./constants.h"

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


    while (true) {
        char command[256] = "";
        printf("sh-%s%s", version, prompt);
        scanf("%s", &command);

        // search through all paths for a file which matches the command
        bool commandFound = false;
        for (int i = 0; i < sizeof(paths); i++) {
            char *constructedCommand = strcat(paths[i], command);
            if (fileExists(constructedCommand)) {
                commandFound = true;
                system(constructedCommand);
            }
        }

        if (!commandFound) {
            printf("sh: command not found: %s\n", command);
        }
    }

    return 0;
}
