#include <stdbool.h>
#include <stdlib.h>
#include "operations.h"

void playerPositionStart(struct slots slot[], struct players player[])
{
	// loop through all players
	for (size_t currentPlayer = 0; currentPlayer < playerNumber; currentPlayer++)
	{
		int random; // integer for random number generated

		// do-while loop to pick a random empty slot
		do
		{
			random = rand()%slotNumber; // get random number between 0 and slotNumber-1
		} while (slot[random].occupied == true); // check if the slot is empty

		slot[random].player = currentPlayer; // slot[random].player is set as the player number
		slot[random].occupied = true; // slot[random].occupied is set as true
		player[currentPlayer].position = random; // player[currentPlayer].position is set as the slot number
	}
}
