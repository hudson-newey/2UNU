#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "./constants.h"

int main(int argc, char const *argv[]) {
    while (true) {
        if (argc < 2) {
            printf("%s", DEFAULT_STRING);
        } else {
            for (int i = 1; i < argc; i++) {
                printf("%s", argv[i]);

                if (i < argc - 1) {
                    printf(" ");
                }
            }
        }

        printf("\n");
    }

    return 0;
}
