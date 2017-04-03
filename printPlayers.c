#include <stdio.h>
#include "operations.h"

void printPlayers (struct players player[])
{
	printf("\n---------------------Players---------------------\n"); // message to user

	char type[4][7] = {"Elf", "Human", "Ogre", "Wizard"}; // array of strings of the player types (order is the same as the enumerator playerTypes

	// for loop to print out information about each player
	for (int printPlayer = 0; printPlayer < playerNumber; printPlayer++)
	{
		char *playerType = type[player[printPlayer].type]; // character pointer to the player type in the array of strings

		printf("%s (%s, %d)\n", player[printPlayer].name, playerType, player[printPlayer].lifePoints); // print out player name, type and their life points
	}
	puts(""); // newline
}
