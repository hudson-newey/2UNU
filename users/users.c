#include <stdio.h>
#include <string.h>
#include <sys/utsname.h>
#include <utmp.h>
#include "users.h"

int main(int argc, const char *argv[]) {
    if (argc > 1) {
        if (strcmp(argv[1], "--version") == 0) {
            printf("%s\n", version);
        } else if (strcmp(argv[1], "--help") == 0) {
            printf("%s\n", helpDocs);
        }
    } else {

        struct utmp *n;
        setutent();
        n = getutent();

        while (n) {
            if (n->ut_type == USER_PROCESS)
            {
                printf("%s ", n->ut_user);
            }
            n = getutent();
        }

        printf("\n");
    }

    return 0;
}
