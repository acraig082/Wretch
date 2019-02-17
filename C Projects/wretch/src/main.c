
#include "wretch.h"

int main(){
	Player * user;
	int ch;
	Position * newPosition;

	char ** level;


	MAX_HEIGHT = 25;
	MAX_WIDTH = 100;

	screenSetup();

	mapSetUp();

	level = saveLevelPositions();

	user = playerSetup();

	while((ch = getch()) != 'q'){
		newPosition = handleInput(ch, user);
		checkPosition(newPosition, user, level);
	}

	endwin();

	return 1;
}

int screenSetup(){
	initscr();
	noecho();
	refresh();

	srand(time(NULL));

	return 0;
}