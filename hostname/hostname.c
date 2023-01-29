#include <stdio.h>

int main(int argc, char const *argv[])
{
    char hostname[1024];
    hostname[1023] = '\0';
    gethostname(hostname, 1023);
    printf("%s\n", hostname);
    return 0;
}
