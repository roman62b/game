#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int get_home_path(char *data_path, const char *data_file) {
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

int main(void) {
	char data_file[] = ".game_usr_data.txt\0";
	char data_path[256] = "type \0";
	get_home_path(data_path, data_file);
	printf("%s\n", data_path);
	system(data_path);
	exit(0);
}