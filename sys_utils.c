// v-0.2.0

// libs
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// header
#include "sys_utils.h"

// WINDOWS
#ifdef _WIN32

void sys_console_clear(void) {
	system("cls");
}

void sys_print_file(const char *path) {
	char command[256] = "type ";
	strcat(command, path);
	system(command);
}

void sys_get_data_path(char *data_path, const char *data_file) {
	//strcat(data_path, "C:\\Users\\%USERNAME%\\");
	strcat(data_path, "C:\\Users\\Roman62\\");
	strcat(data_path, data_file);
}

// LINUX
#elif __linux__

void sys_console_clear(void) {
	system("clear");
}

void sys_print_file(const char *path) {
	char command[256] = "cat ";
	strcat(command, path);
	system(command);
}

void sys_get_data_path(char *data_path, const char *data_file) {
	strcat(data_path, "/home/$(whoami)/");
	strcat(data_path, data_file);
}

#endif