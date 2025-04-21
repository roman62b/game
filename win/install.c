#include <stdio.h>
#include <stdlib.h>

int choice(void) {
	char e;
	again: ;
	scanf("%c", &e);
	if ((e == 'N') || (e == 'n')) {
		return 0;
	} else if ((e == 'Y') || (e == 'y')) {
		return 1;
	} else {
		goto again;
	}
}

int main(void) {
	printf("Installing Tic-Tac-Toe...\n");

	printf("Start the installation? Y/y or N/n\n");
	if (!choice()) exit(0);

	char path[512];
	printf("Installing in C:\\Games\\ ?\n");
	if (choice()) {

	}
	system("mkdir C:\\Games\\Tic-Tac-Toe\\");
	system("copy game.exe C:\\Games\\Tic-Tac-Toe\\");
	system("copy icon.ico C:\\Games\\Tic-Tac-Toe\\");
	system("copy Tic-Tac-Toe.lnk C:\\Games\\Tic-Tac-Toe\\");

	printf("Add a shortcut to your desktop? Y/y or N/n\n");
	if (choice()) system("copy C:\\Games\\Tic-Tac-Toe\\Tic-Tac-Toe.lnk C:\\Users\\%Username%\\Desktop\\Tic-Tac-Toe.lnk");

	//printf("The installation was completed successfully.\n");
	//printf("You can delete this directory.\n");
	printf("Press 'Enter' to exit.\n");
	getchar();
	getchar();
	exit(0);
}