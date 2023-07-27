#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <stdbool.h>
#include <string.h>
#include "sh.h"

// we use fileExists to check if the command exists in PATH
bool fileExists(char *filename)
{
    struct stat buffer;
    return (stat(filename, &buffer) == 0);
}

// some commands (such as cd) are sh commands and not their own applications
bool isProgramCommand(char *command)
{
    // char *programCommands[] = {
    //     "cd"};

    // for (int i = 0; i < sizeof(programCommands); i++)
    // {
    //     if (strcmp(programCommands[i], command) == 0)
    //     {
    //         return true;
    //     }
    // }

    return false;
}

int runCommand(char *currentPathHead, char *command, char *commandArgs)
{
    bool commandFound = false;
    int commandReturnCode = 0;

    // search through current directory
    char *currentDirectoryCommand = strcat(currentPathHead, command);
    if (fileExists(currentDirectoryCommand) && !commandFound)
    {
        char *constructedCommand = strcat(strcat(command, " "), commandArgs);
        system(constructedCommand);
        commandFound = true;
    }

    if (!commandFound) {
        printf("sh: command not found: %s\n", command);
        return 1;
    }
}

int executeProgramCommand(char *command)
{
    return 0;
}

int runFromIoStream(const char *contents)
{
    int i = 0;
    while (contents[i] != EOF)
    {
        i++;
    }

    return 0;
}

int readFromInput()
{
    while (true)
    {
        char currentPathHead[256] = "./";
        char command[256] = "";
        char commandArgs[256] = "";

        printf("\nsh-%s%s", version, prompt);
        char input[512];
        fgets(input, 512, stdin);
        sscanf(input, "%s %s", command, commandArgs);
        if (commandArgs[0] == '\0') {
            strcpy(commandArgs, "");
        }

        // cd command
        if (isProgramCommand(command))
        {
            strcpy(currentPathHead, commandArgs);
        }
        else
        {
            runCommand(currentPathHead, command, commandArgs);
        }
    }
    return 1;
}

int main(int argc, char const *argv[])
{
    if (argc > 1)
    {
        // hard coded commands
        if (strcmp(argv[1], "--help") == 0)
        {
            printf("%s\n", helpDocs);
            return 0;
        }
        else if (strcmp(argv[1], "--version") == 0)
        {
            printf("%s\n", version);
            return 0;
        }

        // run a script file
        runFromIoStream(argv[1]);
    }

    readFromInput();

    return 0;
}
