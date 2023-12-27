#include <stdio.h>
#include <string.h>
#include <sys/utsname.h>
#include "uname.h"

int main(int argc, char const *argv[]) {
    if (argc > 1) {
        if (strcmp(argv[1], "--version") == 0) {
            printf("%s\n", version);
            return 0;
        } else if (strcmp(argv[1], "--help") == 0) {
            printf("%s\n", helpDocs);
            return 0;
        }
    }

    struct utsname uts;
    uname(&uts);
    char *systemName = uts.sysname;

    printf("%s\n", systemName);

    return 0;
}
