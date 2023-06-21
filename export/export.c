#include <stdio.h>

// TODO: this program is incomplete and doesn't support any of the expected CLAs
int main(int argc, const char *argv[], const char *envp[]) {
    for (int i = 0; envp[i] != NULL; i++) {
        printf("%s\n", envp[i]);
    }
    return 0;
}
