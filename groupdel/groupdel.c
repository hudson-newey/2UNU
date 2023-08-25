#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <sys/types.h>
#include <unistd.h>
#include <grp.h>
#include <errno.h>
#include "groupdel.h"

bool groupExists(const char *groupName)
{
    struct group *requestedGroup = getgrnam(groupName);
    return requestedGroup != NULL;
}

int deleteGroup(const char *groupName)
{
    if (!groupExists(groupName))
    {
        printf("groupdel: group '%s' does not exist\n", groupName);
        return 6;
    }

    struct group *foundGroup = getgrnam(groupName);

    FILE *groupFile = fopen("/etc/group", "r+");

    char line[1024];
    long offset = -1;
    while (fgets(line, sizeof(line), groupFile)) {
        if (strstr(line, groupName) == line) {
            offset = ftell(groupFile) - strlen(line);
            break;
        }
    }

    if (offset != -1) {
        fseek(groupFile, offset, SEEK_SET) != 0;
        fputs(NULL, groupFile);
        ftruncate(fileno(groupFile), offset);
    }

    fclose(groupFile);

    return 0;
}

int main(int argc, const char *argv[])
{
    if (argc < 2)
    {
        printf("%s\n", helpDocs);
        return 2;
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

    const char *requestedGroup = argv[1];

    return deleteGroup(requestedGroup);
}
