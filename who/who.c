#include <stdio.h>
#include <sys/utsname.h>
#include <utmp.h>
#include <string.h>
#include "who.h"

int main(int argc, const char *argv[]) {
    if (argc > 1) {
        if (strcmp(argv[1], "--version") == 0) {
            printf("%s\n", version);
            return 0;
        } else if (strcmp(argv[1], "--help") == 0) {
            printf("%s\n", helpDocs);
            return 0;
        }
    }

    struct utmp *n;
    setutent();
    n = getutent();

    while (n) {
        if (n->ut_type == USER_PROCESS)
        {
            printf("%s %6s %8d (%s)\n", n->ut_user, n->ut_line, n->ut_tv.tv_usec, n->ut_host);
        }
        n = getutent();
    }

    return 0;
}
