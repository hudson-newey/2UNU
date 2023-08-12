#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/reboot.h>
#include "reboot.h"

int main(int argc, const char *argv[]) {
    if (argc > 1) {
        if (strcmp(argv[1], "--version") == 0) {
            printf("%s\n", version);
            return 0;
        } else if (strcmp(argv[1], "--help") == 0) {
            printf("%s\n", helpDocs);
            return 0;
        }

        return 1;
    }

    return reboot(RB_AUTOBOOT);
}
