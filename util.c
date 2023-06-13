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

bool contains(char array[128][], char item[128]) {
	for (int i = 0; i < sizeof(array); i++) {
		if (strcmp(array[i], item) == 0) {
			return true;
		}
	}
}
