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

bool directoryExists(char *path)
{
    struct stat buffer;
    return (stat(path, &buffer) == 0);
}

// some commands (such as cd) are sh commands and not their own applications
bool isProgramCommand(char *command)
{
    char *programCommands[] = {"cd", "exit"};

    for (int i = 0; i < 2; i++)
    {
        if (strcmp(programCommands[i], command) == 0)
        {
            return true;
        }
    }

    return false;
}

int runCommand(char *currentPathHead, char *command, char *commandArgs)
{
    // search through current directory
    char *currentDirectoryCommand = strcat(currentPathHead, command);
    if (fileExists(currentDirectoryCommand))
    {
        char *constructedCommand = strcat(strcat(command, " "), commandArgs);
        return system(constructedCommand);
    }

    printf("sh: command not found: %s\n", command);
    return 1;
}

int executeProgramCommand(char *command, char *commandArgs, char *pathHead)
{
    if (strcmp(command, "cd") == 0)
    {
        if (directoryExists(commandArgs))
        {
            strcpy(pathHead, commandArgs);
            return 0;
        }

        printf("sh: cd: %s: No such file or directory\n", commandArgs);
        return 1;
    }
    else if (strcmp(command, "exit") == 0)
    {
        exit(0);
    }

    return 1;
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
    char currentPathHead[PATHS_BUFFER] = "./";
    while (true)
    {
        char command[COMMAND_BUFFER] = "";
        char commandArgs[COMMAND_BUFFER] = "";

        printf("\nsh-%s%s", version, prompt);
        char input[COMMAND_BUFFER];
        fgets(input, COMMAND_BUFFER, stdin);
        sscanf(input, "%s %s", command, commandArgs);
        if (commandArgs[0] == '\0')
        {
            strcpy(commandArgs, "");
        }

        // cd command
        if (isProgramCommand(command))
        {
            executeProgramCommand(command, commandArgs, currentPathHead);
            printf("head: %s\n", currentPathHead);
        }
        else
        {
            // we have to do this otherwise when we use strcat later on its done by reference
            // we instead want to use the value of the variable
            char commandPathHead[PATHS_BUFFER] = "";
            char commandValue[COMMAND_BUFFER] = "";
            char commandArgsValue[COMMAND_BUFFER] = "";

            strcpy(commandPathHead, currentPathHead);
            strcpy(commandValue, command);
            strcpy(commandArgsValue, commandArgs);

            runCommand(commandPathHead, commandValue, commandArgsValue);
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
