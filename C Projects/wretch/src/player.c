#include "wretch.h"

Player * playerSetup(){
	Player * newPlayer;
	newPlayer = malloc(sizeof(Player));

	newPlayer->position.x = 14;
	newPlayer->position.y = 14;
	newPlayer->health = 100;

	mvprintw(newPlayer->position.y, newPlayer->position.x, "@");
	move(newPlayer->position.y, newPlayer->position.x);

	return newPlayer;
}

Position * handleInput(int input, Player * user){
	Position * newPosition;
	newPosition = malloc(sizeof(Position));
	switch(input){
		case 'w':
			newPosition->y = user->position.y - 1;
			newPosition->x = user->position.x;
			break;
		case 'a':
			newPosition->y = user->position.y;
			newPosition->x = user->position.x - 1;
			break;
		case 's':
			newPosition->y = user->position.y + 1;
			newPosition->x = user->position.x;
			break;
		case 'd':
			newPosition->y = user->position.y;
			newPosition->x = user->position.x + 1;
			break;

		default:
			break;
	}

	return newPosition;
}

int checkPosition(Position * newPosition, Player * user, char ** level){
	int space;
	switch(mvinch(newPosition->y, newPosition->x)){
		case '.':
		case '#':
		case '+':
			playerMove(newPosition, user, level);
			break;
		default:
			move(user->position.y, user->position.x);
			break;

	}
}

int playerMove(Position * newPosition, Player * user, char ** level){

	char buffer[8];

	

	sprintf(buffer, "%c", level[user->position.y][user->position.x]);

	mvprintw(user->position.y, user->position.x, buffer);

	user->position.y = newPosition->y;
	user->position.x = newPosition->x;

	mvprintw(user->position.y, user->position.x, "@");
	move(user->position.y, user->position.x);
}