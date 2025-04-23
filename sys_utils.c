// v-0.1.0

// libs
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// header
#include "sys_utils.h"

int sys_console_clear(void) {
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

int sys_print_file(const char *path) {
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

int sys_get_data_path(char *data_path, const char *data_file) {
	#ifdef _WIN32
		strcat(data_path, "C:\\Users\\%USERNAME%\\");
		strcat(data_path, data_file);
		return 0;
	#elif __linux__
		strcat(data_path, "/home/$(whoami)/");
		strcat(data_path, data_file);
		return 0;
	#else
		printf("Unknown OS!\n");
		return 1;
	#endif
}