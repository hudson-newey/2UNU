#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <errno.h>
#include <string.h>
#include <dirent.h>
#include <ctype.h>
#include "pidof.h"

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

int printPidOfProcess(const char *processName)
{
    const pid_t pid = getPidFromName(processName);

    if (pid == -1)
    {
        return 1;
    }

    printf("%d\n", pid);

    return 0;
}

int main(int argc, const char *argv[])
{
    if (argc < 2)
    {
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

    const char *requestedProgram = argv[1];
    return printPidOfProcess(requestedProgram);
}
