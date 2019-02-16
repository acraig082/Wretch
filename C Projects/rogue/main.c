#include <ncurses.h>
#include <stdlib.h>
#include <time.h>


typedef struct Position{
	int x;
	int y;
	//TILE_TYPE tile;

} Position;

typedef struct Room{
	Position position;
	int height;
	int width;

	Position ** doors;
	//Monster ** monsters;
	//Item ** items; 
} Room;

typedef struct Player{
	Position position;
	int health;
	//Room * room;
} Player;

int screenSetup();
Room ** mapSetUp();
Player * playerSetup();
int handleInput(int ch, Player * user);
int checkPosition(int newY, int newX, Player * user);
int playerMove(int x, int y, Player * user);

/* room functions */
Room * createRoom(int y, int x, int height, int width);
int drawRoom(Room * room);
int connectDoors(Position * door1, Position * door2);

int main(){
	Player * user;
	int ch;

	screenSetup();

	mapSetUp();
	
	user = playerSetup();

	while((ch = getch()) != 'q'){
		handleInput(ch, user);
	}

	endwin();

	return 1;
}

int screenSetup(){
	initscr();
	//printw("Hello World!");
	noecho();
	refresh();

	srand(time(NULL));

	return 0;
}

Room ** mapSetUp(){
	Room ** rooms;
	rooms = malloc(sizeof(Room)*3);
	int i;

	rooms[0] = createRoom(13, 13, 6, 8);
	rooms[1] = createRoom(2, 40, 6, 8);
	rooms[2] = createRoom(13, 40, 6, 12);
	
	for(i = 0; i < 3; i++){
		drawRoom(rooms[i]);
	}

	connectDoors(rooms[0]->doors[3], rooms[2]->doors[1]);
	connectDoors(rooms[2]->doors[0], rooms[1]->doors[3]);

	return rooms;	
}

Room * createRoom(int y, int x, int height, int width){
	Room * newRoom;
	newRoom = malloc(sizeof(Room));

	newRoom->position.x = x;
	newRoom->position.y = y;
	newRoom->height = height;
	newRoom->width = width;

	newRoom->doors = malloc(sizeof(Position) * 4);

	/* top door */
	newRoom->doors[0] = malloc(sizeof(Position));
	newRoom->doors[0]->x = (rand() % (width-3)) + newRoom->position.x + 1;
	newRoom->doors[0]->y = newRoom->position.y;
	/* left door */
	newRoom->doors[1] = malloc(sizeof(Position));
	newRoom->doors[1]->x = newRoom->position.x;
	newRoom->doors[1]->y = (rand() % (height-3)) + newRoom->position.y + 1;
	/* bottom door */
	newRoom->doors[2] = malloc(sizeof(Position));
	newRoom->doors[2]->x = (rand() % (width-3)) + newRoom->position.x + 1;
	newRoom->doors[2]->y = newRoom->position.y + newRoom->height -1;
	/* right door */
	newRoom->doors[3] = malloc(sizeof(Position));
	newRoom->doors[3]->x = newRoom->position.x + newRoom->width - 1;
	newRoom->doors[3]->y = (rand() % (height-3)) + newRoom->position.y + 1;

	return newRoom;
}

int drawRoom(Room * room){
	int y;
	int x;

	room->width--;
	room->height--;

	/* draw room*/
	for(x = room->position.x; x <= room->position.x + room->width;x++){
		for(y = room->position.y; y <= room->position.y + room->height;y++){
			if(y == room->position.y || y == room->position.y + room->height){
				mvprintw(y, x, "-");
			} else if(x == room->position.x || x == room->position.x + room->width){
				mvprintw(y, x, "|");
			} else{
				mvprintw(y, x, ".");
			}
		}
	}

	/* draw doors */
	mvprintw(room->doors[0]->y, room->doors[0]->x, "+");
	mvprintw(room->doors[1]->y, room->doors[1]->x, "+");
	mvprintw(room->doors[2]->y, room->doors[2]->x, "+");
	mvprintw(room->doors[3]->y, room->doors[3]->x, "+");

	return 1;
}

int connectDoors(Position * door1, Position * door2){
	Position temp;

	temp.x = door1->x;
	temp.y = door1->y;

	while(1){
		/* step left*/
		if((abs((temp.x - 1) - door2->x) < abs(temp.x - door2->x)) && (mvinch(temp.y, temp.x - 1) == ' ')){
			mvprintw(temp.y, temp.x - 1, "#");
			temp.x = temp.x - 1;
		}
		/* step right*/
		else if((abs((temp.x + 1) - door2->x) < abs(temp.x - door2->x)) && (mvinch(temp.y, temp.x + 1) == ' ')){
			mvprintw(temp.y, temp.x + 1, "#");
			temp.x = temp.x + 1;
		}
		/* step down*/
		else if((abs((temp.y + 1) - door2->y) < abs(temp.y - door2->y)) && (mvinch(temp.y + 1, temp.x) == ' ')){
			mvprintw(temp.y + 1, temp.x, "#");
			temp.y = temp.y + 1;
		}
		/* step up*/
		else if((abs((temp.y - 1) - door2->y) < abs(temp.y - door2->y)) && (mvinch(temp.y - 1, temp.x) == ' ')){
			mvprintw(temp.y - 1, temp.x, "#");
			temp.y = temp.y - 1;
		} else {
			return 0;
		}

		getch();
	}

	return 1;
}

Player * playerSetup(){
	Player * newPlayer;
	newPlayer = malloc(sizeof(Player));

	newPlayer->position.x = 14;
	newPlayer->position.y = 14;
	newPlayer->health = 100;

	playerMove(14, 14, newPlayer);

	return newPlayer;
}

int handleInput(int input, Player * user){
	int newY;
	int newX;
	switch(input){
		case 'w':
			newY = user->position.y - 1;
			newX = user->position.x;
			break;
		case 'a':
			newY = user->position.y;
			newX = user->position.x - 1;
			break;
		case 's':
			newY = user->position.y + 1;
			newX = user->position.x;
			break;
		case 'd':
			newY = user->position.y;
			newX = user->position.x + 1;
			break;

		default:
			break;
	}

	checkPosition(newY, newX, user);
}

int checkPosition(int newY, int newX, Player * user){
	int space;
	switch(mvinch(newY, newX)){
		case '.':
		case '#':
		case '+':
			playerMove(newY, newX, user);
			break;
		default:
			move(user->position.y, user->position.x);
			break;

	}
}

int playerMove(int y, int x, Player * user){
	mvprintw(user->position.y, user->position.x, ".");

	user->position.y = y;
	user->position.x = x;

	mvprintw(user->position.y, user->position.x, "@");
	move(user->position.y, user->position.x);
}