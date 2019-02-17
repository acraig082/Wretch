#include "wretch.h"
#include "utils.h"

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

// int connectDoors(Position * door1, Position * door2){
// 	Position temp;
// 	Position previous;
// 	int count = 0;

// 	temp.x = door1->x;
// 	temp.y = door1->y;

// 	previous = temp;

// 	while(1){
// 		/* step left*/
// 		if((abs((temp.x - 1) - door2->x) < abs(temp.x - door2->x)) && (mvinch(temp.y, temp.x - 1) == ' ')){
// 			previous.x = temp.x;
// 			temp.x = temp.x - 1;
// 		}
// 		/* step right*/
// 		else if((abs((temp.x + 1) - door2->x) < abs(temp.x - door2->x)) && (mvinch(temp.y, temp.x + 1) == ' ')){
// 			previous.x = temp.x;
// 			temp.x = temp.x + 1;
// 		}
// 		/* step down*/
// 		else if((abs((temp.y + 1) - door2->y) < abs(temp.y - door2->y)) && (mvinch(temp.y + 1, temp.x) == ' ')){
// 			previous.y = temp.y;
// 			temp.y = temp.y + 1;
// 		}
// 		/* step up*/
// 		else if((abs((temp.y - 1) - door2->y) < abs(temp.y - door2->y)) && (mvinch(temp.y - 1, temp.x) == ' ')){
// 			previous.y = temp.y;
// 			temp.y = temp.y - 1;
// 		} else {
// 			if(count == 0){
// 				temp = previous;
// 				count++;
// 				continue;
// 			}
// 			else{
// 				return 0;
// 			}
			
// 		}

// 		mvprintw(temp.y, temp.x, "#");

// 		getch();
// 	}

// 	return 1;
// }




//}