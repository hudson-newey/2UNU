#include <stdio.h>
#include <string.h>
#include "./constants.h"

void addEscapeSeq(char *ptr)
{
	char *temp;
	while (strstr(ptr, "\\n") || strstr(ptr, "\\t") || strstr(ptr, "\\r"))
	{
		if (temp = strstr(ptr, "\\n"))
		{
			*temp = 10;
			strcpy(temp + 1, temp + 2);
		}
		else if (temp = strstr(ptr, "\\r"))
		{
			*temp = 13;
			strcpy(temp + 1, temp + 2);
		}
		else if (temp = strstr(ptr, "\\t"))
		{
			*temp = 9;
			strcpy(temp + 1, temp + 2);
		}
	}
}

int main(int argc, char const *argv[])
{
	if (argc > 1)
	{
		if (strcmp(argv[1], "-e") == 0)
		{
			char *str = argv[2];
			addEscapeSeq(str);
			printf("%s", str);
			printf("%s", newLineCharacter);
		}
		else
		{
			if (strcmp(argv[1], "-n") == 0)
			{
				printf("%s", argv[2]);
			}
			else
			{
				printf("%s", argv[1]);
				printf("%s", newLineCharacter);
			}
		}
	}

	return 0;
}
