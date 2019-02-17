#ifndef WRETCH_H
#define WRETCH_H

#include <ncurses.h>
#include <stdlib.h>
#include <time.h>
//#include "queue.h"
//#include "utils.h"

/****************** Struct Definitions ****************/

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

/***************** Global Variables *******************/
int MAX_HEIGHT;
int MAX_WIDTH;

/***************** Screen Functions *******************/
int screenSetup();

/***************** Level/Map Functions *******************/
Room ** mapSetUp();
char ** saveLevelPositions();

/***************** Player Functions *******************/
Player * playerSetup();
Position * handleInput(int ch, Player * user);
int checkPosition(Position * newPosition, Player * user, char ** level);
int playerMove(Position * newPosition, Player * user, char ** level);

/***************** Room Functions *******************/
Room * createRoom(int y, int x, int height, int width);
int drawRoom(Room * room);
int connectDoors(Position * door1, Position * door2);

#endif