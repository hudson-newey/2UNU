#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <errno.h>
#include <stdbool.h>
#include "rmdir.h"


bool isDirEmpty(const char *path)
{
	struct dirent *ent;
	bool ret = true;

	DIR *d = opendir(path);
	if (!d) {
		fprintf(stderr, "%s: ", path);
		perror("");
		return -1;
	}

	while ((ent = readdir(d))) {
		if (!strcmp(ent->d_name, ".") || !(strcmp(ent->d_name, "..")))
			continue;
		ret = false;
		break;
	}

	closedir(d);
	return ret;
}

void deleteDirectory(char *dirPath) {
}

int main(int argc, const char *argv[]) {
    if (argc < 2) {
        printf("rmdir: missing operand\nTry 'rmdir --help' for more information.\n");
        return 1;
    }

    if (strcmp(argv[1], "--version") == 0) {
        printf("%s\n", version);
        return 0;
    } else if (strcmp(argv[1], "--help") == 0) {
        printf("%s\n", helpDocs);
        return 0;
    }

    char *dirPath = argv[1];

    // check if the directory exists
    DIR* dir = opendir(dirPath);
    if (dir) {
        // check if the directory is empty
        if (isDirEmpty(dirPath)) {
            rmdir(dirPath);
            return 0;
        } else {
            printf("rmdir: failed to remove '%s': Directory not empty\n", dirPath);
            return 1;
        }
    } else if (ENOENT == errno) {
        // here the path does not exist
        printf("rmdir: failed to remove '%s': No such file or directory\n", dirPath);
        return 1;
    }

    return 0;
}
