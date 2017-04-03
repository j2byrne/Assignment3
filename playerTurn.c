#include <stdio.h>
#include <stdbool.h>
#include "operations.h"

void playerTurn(struct slots slot[], struct players player[], int currentPlayer)
{
	int previousSlot = (player[currentPlayer].position-1 + slotNumber) % slotNumber; // previous slot to the one that the player is in, equation to account for negative values
	int nextSlot = (player[currentPlayer].position+1) % slotNumber;// next slot to the one that the player is in, equation to account for when the number is greater than or equal to the slotNumber
	enum playerActions playerAction; // enum playerActions to store what the player is going to do

	printf("Please enter 0 if you want to attack or 1 if you want to move: "); // prompt
	scanf("%d", &playerAction); // read integer which is saved in the enumeration playerAction to determine whether the player wants to attack another player or move position

	// switch to determine the players action
	switch (playerAction)
	{
		case ATTACK: // case for when player wants to attack
			playerAttack(slot, player, currentPlayer, previousSlot, nextSlot);
			break;
		case MOVE: // case for when player wants to move position
			playerMove(slot, player, currentPlayer, previousSlot, nextSlot); // call playerMove function
			break;
		default:
			break;
	}
}
