#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include "pkill.h"

int killProcessById(int pid) {
    if (pid <= 0) {
        return 1;
    }
    
    if (kill(pid, SIGKILL) != 0) {
        return 1;
    }

    return 0;
}

int main(int argc, const char *argv[]) {
    if (argc < 2) {
        printf("pkill: no matching criteria specified\nTry `pkill --help' for more information.\n");
        return 2;
    }

    if (strcmp(argv[1], "--version") == 0) {
        printf("%s\n", version);
        return 0;
    } else if (strcmp(argv[1], "--help") == 0) {
        printf("%s\n", helpDocs);
        return 0;
    }

    int processId = atoi(argv[1]);
    return killProcessById(processId);
}
