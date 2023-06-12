#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "./constants.h"

#define false 0
#define true 1

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

bool contains(char array[128][], char item[128]) {
	for (int i = 0; i < sizeof(array); i++) {
		if (strcmp(array[i], item) == 0) {
			return true;
		}
	}
}

int main(int argc, char const *argv[]) {
	bool includeNewline = !contains(argv, newLineCla);
	bool includeEscapeSeq = !contains(argv, escapeSeqCla);

	if (includeEscapeSeq) {
		const char *str = argv[1];
		addEscapeSeq(str);
		printf("%s", str);
	} else {
		printf("%s", argv[1]);
	}

	if (includeNewline) {
		printf("%s", newLineCharacter);
	}

	return 0;
}
