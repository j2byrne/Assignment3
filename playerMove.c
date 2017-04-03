#include <stdio.h>
#include <stdbool.h>
#include "operations.h"

void playerMove(struct slots slot[], struct players player[], int currentPlayer, int previousSlot, int nextSlot) // function to complete a players move
{
	int playerMove; // position that the player will move to
	int moveSlot; // user choice to move player
	int currentSlot = player[currentPlayer].position; // currentSlot int storing the position of the currentPlayer

	if (slot[previousSlot].occupied != false && slot[nextSlot].occupied != false) // When there are no empty neighboring slots
	{
		printf("\nThere are no empty neighboring slots, you must attack!\n"); // message
		playerAttack(slot, player, currentPlayer, previousSlot, nextSlot); // call player attack function as player cannot move
	}
	if (slot[previousSlot].occupied == false && slot[nextSlot].occupied == true) // check if the only neighboring slot is the previous slot
	{
		printf("\nYou will move to the previous slot (slot %d) as the next slot (slot %d) is occupied by another player\n", previousSlot, nextSlot); // message to user indicating that they will move to the previous slot
		playerMove = previousSlot; // setting playerMove to the previousSlot
	}
	else if (slot[previousSlot].occupied == true && slot[nextSlot].occupied == false)  // check if the only neighboring slot is the next slot
	{
		printf("\nYou will move to the next slot (slot %d) as the previous slot (slot %d) is occupied by another player\n", nextSlot, previousSlot); // message to user indicating that they will move to the next slot
		playerMove = nextSlot; // setting playerMove to the nextSlot
	}
	else //if (slot[previousSlot].occupied == false && slot[nextSlot].occupied == false) // check if the only neighboring slot is the previous slot
	{
		// do while loop to see which slot the player wants to move to and check if the input is valid
		do
		{
			printf("\nPlease enter 0 to move to the previous slot (slot %d) or 1 to move to the next slot (slot %d): ", previousSlot, nextSlot); // prompt
			scanf("%d", &moveSlot); // read user input for which slot they want to move to
		} while (moveSlot > 1 || moveSlot < 0); // check if the input is valid
		(moveSlot == 0) ? (playerMove = previousSlot) : (playerMove = nextSlot); // conditional to set the playerMove to the number of the slot that the user wants the player to move to
	}

	slot[currentSlot].occupied = false; // set slot that the player was in to being not occupied
	slot[playerMove].occupied = true; // set slot that the player is moving to to being occupied
	slot[playerMove].player = currentPlayer; // set the number of the player to the slot
	player[currentPlayer].position = playerMove; // change the slot the player is in to the number of the new slot

	// apply changes to the current players capabilities based on the slot they moved to and their current capabilities
	switch (slot[playerMove].type)
	{
		case CITY: // if player moved to a city
			if (player[currentPlayer].smartness > 60) // if current players smartness is greater than 60
			{
				player[currentPlayer].magicSkills += 10; // add 10 to players magic skills
				if (player[currentPlayer].magicSkills > 100) // if player magic skills is greater to 100 set magic skills to 100
					player[currentPlayer].magicSkills = 100;
			}
			else if (player[currentPlayer].smartness <= 50)// if current players smartness is less than or equal to 50
			{
				player[currentPlayer].dexterity -= 10;// subtract 10 from players dexterity
				if (player[currentPlayer].dexterity < 0)// if player dexterity is less  than 0 set player dexterity to 0
					player[currentPlayer].dexterity = 0;
			}
			break;
		case HILL:
			if (player[currentPlayer].dexterity >= 60) // if current players dexterity is greater than 60
				{
					player[currentPlayer].strength += 10; // add 10 to players strength
					if (player[currentPlayer].strength > 100) // if player strength is greater to 100 set strength to 100
						player[currentPlayer].strength = 100;
				}
				else if (player[currentPlayer].dexterity < 50)// if current players dexterity is less than or equal to 50
				{
					player[currentPlayer].strength -= 10;// subtract 10 from players dexterity
					if (player[currentPlayer].strength < 0)// if player dexterity is less  than 0 set player strength to 0
						player[currentPlayer].strength = 0;
				}
			break;
		// note there are no changes to player capabilities if the slot is a level ground
		default:
			break;
	}

	printf("\nThe player %d is now in slot %d\n", currentPlayer, player[currentPlayer].position);
}
