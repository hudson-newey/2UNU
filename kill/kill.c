#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <errno.h>
#include <string.h>
#include "kill.h"

int killProcessById(const pid_t pid)
{
    if (pid <= 0)
    {
        // I personally don't think this is a good error message
        // however, it is the industry default, so I'll let it be
        printf("kill: not enough arguments\n");
        return 1;
    }

    const int returnValue = kill(pid, SIGKILL);

    if (returnValue == -1) {
        switch (errno) {
            case ESRCH:
                printf("kill: kill %d failed: no such process\n", pid);
                break;
            case EINVAL:
                printf("kill: kill %d failed: invalid signal\n", pid);
                break;
            default:
                perror("kill");
        }
    }

    return returnValue;
}

int main(int argc, const char *argv[])
{
    if (argc < 2)
    {
        printf("kill: not enough arguments\n");
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

    const pid_t processId = atoi(argv[1]);
    return killProcessById(processId);
}
