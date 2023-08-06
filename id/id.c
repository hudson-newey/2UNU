#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <grp.h>
#include <pwd.h>
#include <string.h>
#include "id.h"

#define MAX_USERID_LENGTH 32

void printUserGroup(char *username) {
    struct group *grp = getgrnam(username);
    printf("%d(%s)", grp->gr_gid, grp->gr_name);
}

int printUserId(char *username) {
    if (username == NULL) {
        return 1;
    }

    struct passwd *pw_entry = getpwnam(username);

    if (pw_entry == NULL) {
        perror("getpwnam");
        return 1;
    }

    // uid=1000(grathium) gid=1000(grathium) groups=1000(grathium),492(dialout)
    __uid_t uid = pw_entry->pw_uid;
    __gid_t gid = pw_entry->pw_gid;

    printf(
        "uid=%d(%s) gid=%d(%s) groups=",
        uid,
        username,
        gid,
        username
    );

    printUserGroup(username);

    printf("\n");

    return 0;
}

int printCurrentUserId() {
    char currentUserUsername[MAX_USERID_LENGTH];
    cuserid(currentUserUsername);

    if (currentUserUsername == NULL) {
        return 1;
    }

    printUserId(currentUserUsername);

    return 0;
}

int main(int argc, const char *argv[]) {
    if (argc > 1) {
        if (strcmp(argv[1], "--version") == 0) {
            printf("%s\n", version);
            return 0;
        } else if (strcmp(argv[1], "--help") == 0) {
            printf("%s\n", helpDocs);
            return 0;
        }

        const char *username = argv[1];
        return printUserId(username);
    }

    return printCurrentUserId();
}
