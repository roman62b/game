// v-0.1.0

// libs
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// header
#include "sysapi.h"

int console_clear(void) {
	#ifdef _WIN32
		system("cls");
		return 0;
	#elif __linux__
		system("clear");
		return 0;
	#else
		printf("Unknown OS!\n");
		return 1;
	#endif
}

int print_file(const char *path) {
	if (!strlen(path)) printf("Path error.\n");
	#ifdef _WIN32
		char command[256] = "type ";
		strcat(command, path);
		system(command);
		return 0;
	#elif __linux__
		char command[256] = "cat ";
		strcat(command, path);
		system(command);
		return 0;
	#else
		printf("Unknown OS!\n");
		return 1;
	#endif
}