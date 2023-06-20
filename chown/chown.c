#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <stdbool.h>
#include <unistd.h>
#include <grp.h>
#include <pwd.h>
#include "chown.h"

bool fileExists(char *filePath) {
  struct stat buffer;
  return stat(filePath, &buffer) == 0;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("chown: missing operand\nTry 'chown --help' for more information.\n");
        return 1;
    } else if (argc < 3) {
        if (strcmp(argv[1], "--version") == 0) {
            printf("%s\n", version);
            return 0;
        } else if (strcmp(argv[1], "--help") == 0) {
            printf("%s\n", helpDocs);
            return 0;
        }

        printf("chown: missing operand after '%s'\nTry 'chown --help' for more information.\n", argv[1]);
        return 1;
    }

    char *userInputString = argv[1];
    char *filePath = argv[2];

    if (!fileExists(filePath)) {
        printf("chown: cannot access '%s': No such file or directory\n", filePath);
        return 1;
    }

    // I need to convert the user to a user id, so that I can assign the file to the user id
    struct passwd *user = getpwnam(userInputString);

    if (user == NULL) {
        printf("chown: invalid user: '%s'\n", userInputString);
        return 1;
    }

    // TODO: this should support group assignment
    chown(filePath, user->pw_uid, user->pw_gid);

    // TODO: need to add post checks to verify if the owner was actually changed. If not, throw an error

    return 0;
}
