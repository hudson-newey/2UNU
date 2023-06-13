#include <stdio.h>
#include <string.h>
#include "./constants.h"

void addEscapeSeq(char *ptr) {
	char *temp;
	while (strstr(ptr, "\\n") || strstr(ptr, "\\t") || strstr(ptr, "\\r")) {
		if (temp = strstr(ptr, "\\n")) {
			*temp = 10;
			strcpy(temp + 1, temp + 2);
		} else if (temp = strstr(ptr, "\\r")) {
			*temp = 13;
			strcpy(temp + 1, temp + 2);
		} else if (temp = strstr(ptr, "\\t")) {
			*temp = 9;
			strcpy(temp + 1, temp + 2);
		}
	}
}

void printEscapedString(char *str) {
    addEscapeSeq(str);
    printf("%s", str);
}

int main(int argc, char const *argv[]) {
    if (strcmp(argv[1], "--version") == 0) {
        printEscapedString(version);
    } else if (strcmp(argv[1], "--help") == 0) {
        printEscapedString(helpDocs);
    } else {
        const char *str = argv[1];
        printEscapedString(str);
    }

	return 0;
}
