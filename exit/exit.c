#include <stdio.h>

int main(int argc, char const *argv[]) {
	if (argc > 1) {
		exit(argv[1]);
	} else {
		exit(0);
	}

	return 100;
}
