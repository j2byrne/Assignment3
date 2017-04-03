#include <stdio.h>
#include "operations.h"

void playerAttack(struct slots slot[], struct players player[], int currentPlayer, int previousSlot, int nextSlot)
{
	int playerAttacked; // player that is going to be attacked

	if (slot[previousSlot].occupied == true && slot[nextSlot].occupied == true) // check if there is a player in both slots previousSlots and nextSlots
	{
		int attackedPlayer; // integer to store value of users choice of player to attack

		// do while loop to see which player the current player wants to attack
		do
		{
			printf("Please enter 0 to attack player %d whose in slot %d or 1 to attack player %d whose in slot %d: ", slot[previousSlot].player+1, previousSlot, slot[nextSlot].player+1, nextSlot); // prompt
			scanf("%d", &attackedPlayer); // read user input for which player they want to attack
		} while (attackedPlayer > 1 || attackedPlayer < 0); // check if the input is valid

		(attackedPlayer == 0) ? (playerAttacked = slot[previousSlot].player) : (playerAttacked = slot[nextSlot].player); // conditional to set the playerAttacked to the players position the the curent player wants to attack
	}
	else if (slot[previousSlot].occupied == true && slot[nextSlot].occupied == false)  // check if there is a player in the slot previousSlots and no player in the slot nextSlots
	{
		playerAttacked = slot[previousSlot].player; // assigning who the playerAttacked will be
		printf("You will attack player %d, who is in slot %d\n", playerAttacked+1, previousSlot); // message to user
	}
	else if (slot[previousSlot].occupied == false && slot[nextSlot].occupied == true) // check if there is a player in the slot nextSlots and no player in the slot previousSlots
	{
		playerAttacked = slot[nextSlot].player; // assigning who the playerAttacked will be
		printf("You will attack player %d, who is in slot %d\n", playerAttacked+1, nextSlot); // message to user
	}
	else
	{
		previousSlot = (previousSlot-1 + slotNumber)%slotNumber; // decrease previousSlot by 1, if reaches -1, assigns slotNumber-1
		nextSlot = (nextSlot+1)%slotNumber; // increase nextSlot by 1, if reaches slotNumber, assigns 0

		playerAttack(slot, player, currentPlayer, previousSlot, nextSlot); // recursion to find the closest slot with a player in it
		return;
	}

	if (player[playerAttacked].strength <= 70) // if the playerAttacked points is less than or equal to 70
		player[playerAttacked].lifePoints -= 0.5 * player[playerAttacked].strength; // reduce playerAttacked lifePoints
	else if (player[playerAttacked].strength > 70)  // if the playerAttacked points is greater than 70
		player[currentPlayer].lifePoints -= 0.3 * player[playerAttacked].strength; // reduce currentPlayer lifePoints
}
