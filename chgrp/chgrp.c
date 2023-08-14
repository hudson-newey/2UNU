#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <grp.h>
#include <string.h>
#include <stdbool.h>
#include "chgrp.h"

bool fileExists(const char *filePath) {
  struct stat buffer;
  return stat(filePath, &buffer) == 0;
}

int changeGroupOwnership(const char *groupName, const char *filePath) {
    if (!fileExists(filePath)) {
        printf("chgrp: cannot access '%s': No such file or directory\n", filePath);
        return 1;
    }

    struct group *grp = getgrnam(groupName);
    if (grp == NULL) {
        printf("chgrp: invalid group: 'rsdaskdjas'\n", groupName);
        return 1;
    }

    gid_t newGroupId = grp->gr_gid;

    if (chown(filePath, -1, newGroupId) == -1) {
        return 1;
    }

    return 0;
}

int main(int argc, const char *argv[]) {
    if (argc < 2) {
        printf("chgrp: missing operand\nTry 'chgrp --help' for more information.\n");
        return 1;
    }
    
    if (strcmp(argv[1], "--version") == 0) {
        printf("%s\n", version);
        return 0;
    } else if (strcmp(argv[1], "--help") == 0) {
        printf("%s\n", helpDocs);
        return 0;
    }

    const char *groupName = argv[1];

    // usage: chgrp <group_name> <file_path>
    // therefore, we need 3 arguments
    if (argc < 3) {
        printf("chgrp: missing operand after '%s'\nTry 'chgrp --help' for more information.\n", groupName);
    }

    const char *filePath = argv[2];

    return changeGroupOwnership(groupName, filePath);
}
