#include <stdio.h>
#include <stdlib.h>
#include "operations.h"

int main(void) {
	int playerNumber;

	struct players *playerPtr = NULL;

	//pointer to slot (0,0)
	struct slot *upLeft;
	//pointer to slot (0,boardSize -1)
	struct slot *upRight;
	//pointer to slot (boardSize - 1, 0)
	struct slot *downLeft;
	//pointer to slot (boardSize - 1, boardSize -1)
	struct slot *downRight;

	//Creates the board
	createBoard(BOARD_SIZE, &upLeft, &upRight, &downLeft, &downRight);

	// randomly assigns each slot a random type
	slotInitialize(&upLeft);

	printBoard(&upLeft); // print board

	playerInitialize(&playerPtr, &playerNumber);

	printPlayers(&playerPtr, &playerNumber);
}
