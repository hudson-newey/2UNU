#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <sys/types.h>
#include <grp.h>
#include "groupadd.h"

bool groupExists(const char *groupName)
{
    struct group *foundGroup = getgrnam(groupName);
    return foundGroup != NULL;
}

__gid_t nextGroupNumberAvailable()
{
    setgrent();

    __gid_t maxGroupId = 0;
    struct group *foundGroup;

    while ((foundGroup = getgrent()) != NULL)
    {
        if (foundGroup->gr_gid > maxGroupId)
        {
            maxGroupId = foundGroup->gr_gid;
        }
    }

    endgrent();

    return maxGroupId + 1;
}

int createGroup(const char *groupName)
{
    if (groupExists(groupName))
    {
        printf("groupadd: group '%s' already exists\n", groupName);
        return 9;
    }

    __gid_t newGroupId = nextGroupNumberAvailable();

    struct group newGroup;
    newGroup.gr_name = groupName;
    newGroup.gr_mem = NULL;
    newGroup.gr_gid = newGroupId;

    FILE *groupFile = fopen("/etc/group", "a");

    int result = putgrent(&newGroup, groupFile);

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

    const char *newGroupName = argv[1];

    return createGroup(newGroupName);
}
