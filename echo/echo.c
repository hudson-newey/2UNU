#include <stdio.h>
#include <string.h>
#include "./constants.h"

int replace(char* source, char search[], char replace[]) {
        char* value = (char *)malloc( ( strlen(source) - strlen(search) ) + strlen(replace) );
 
        char* start = strstr(source, search);
        strncpy(value, source, *start); 

        printf("%s\n", value);

        return 0;
}

int main(int argc, char const *argv[]) {
        if (argc > 1) {
                if (strcmp(argv[1], "-e") == 0) {
                        printf("escape characters");
                } else {
                        // print as is
                        printf("%s", argv[1]);
                }

        }

        printf("%s", newLineCharacter);
        return 0;
}
