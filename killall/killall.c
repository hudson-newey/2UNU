#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <errno.h>
#include <string.h>
#include <dirent.h>
#include <ctype.h>
#include "killall.h"

int killProcessById(const pid_t pid)
{
    if (pid <= 0)
    {
        // I personally don't think this is a good error message
        // however, it is the industry default, so I'll let it be
        printf("killall: not enough arguments\n");
        return 1;
    }

    const int returnValue = kill(pid, SIGKILL);

    if (returnValue == -1)
    {
        switch (errno)
        {
        case ESRCH:
            printf("killall: kill %d failed: no such process\n", pid);
            break;
        case EINVAL:
            printf("killall: kill %d failed: invalid signal\n", pid);
            break;
        default:
            perror("kill");
        }
    }

    return returnValue;
}

// TODO: this is ChatGPT generated and I don't like it
const pid_t getPidFromName(const char *processName)
{
    DIR *dir;
    struct dirent *ent;
    char *endptr;
    char buf[2048];

    dir = opendir("/proc");

    while ((ent = readdir(dir)) != NULL)
    {
        if (isdigit(*ent->d_name))
        {
            const long lpid = strtol(ent->d_name, &endptr, 10);
            if (*endptr != '\0')
            {
                continue;
            }

            snprintf(buf, sizeof(buf), "/proc/%ld/comm", lpid);
            FILE *fp = fopen(buf, "r");
            if (fp)
            {
                if (fgets(buf, sizeof(buf), fp))
                {
                    buf[strcspn(buf, "\n")] = 0;

                    if (strcmp(buf, processName) == 0)
                    {
                        fclose(fp);
                        closedir(dir);
                        return (pid_t)lpid;
                    }
                }

                fclose(fp);
            }
        }
    }

    closedir(dir);
    return -1;
}

int killProgramByName(const char *processName)
{
    const pid_t pid = getPidFromName(processName);

    if (pid == -1)
    {
        printf("%s: no process found\n", processName);
        return 1;
    }

    return killProcessById(pid);
}

int main(int argc, const char *argv[])
{
    if (argc < 2)
    {
        printf("%s\n", helpDocs);
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

    const char *programName = argv[1];
    return killProgramByName(programName);
}
