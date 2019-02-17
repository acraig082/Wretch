#include "wretch.h"
#include "utils.h"

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

	
	//connectDoors(rooms[0]->doors[3], rooms[2]->doors[1]);
	pathFind(rooms[0]->doors[3], rooms[2]->doors[1]);
	//connectDoors(rooms[2]->doors[0], rooms[1]->doors[3]);

	return rooms;	
}

char ** saveLevelPositions() {
	int x, y;
	char ** positions;
	positions = malloc(sizeof(char *) * 25);

	for(y = 0; y < 25; y++)
	{
		positions[y] = malloc(sizeof(char) * 100);
		for(x = 0; x < 100; x++)
		{
			positions[y][x] = mvinch(y, x);
		}
	}

	return positions;
}