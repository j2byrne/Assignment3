#include <stdio.h>
#include <stdlib.h>
#include "operations.h"

void attack(int currPlayer, int playerNumber, struct slot **upLeft, struct slot **upRight, struct slot **downLeft, struct slot **downRight)
{
	enum attackTypes attackType;
	int defenderPlayer;
	int a,b,c,d; // row and column for both attacking and defending player
	int z; // distance from

	printf("You have decided to attack\n"); // The current player has choosen to attack this round
	printf("Enter 0 for near attack, 1 for distant attack, 2 for magic attack: "); // player decides which attack to use
	scanf("%d",&attackType);

	printf("\nEnter the number of the player you wish to attack out of the following list\n"); //prompt

	for (int i= 0; i < playerNumber; i++)
	{
		if (currPlayer != i && player[i].lifePoints != 0)
			printf("Do you want to attack %s, player %d\n", player[i].name, i+1); // asks the user which player they want to attack
	}
	printf("? "); // prompt

	scanf("%d",&defenderPlayer); // read user input
	defenderPlayer--; // players start at 0 not at 1
	
	while (defenderPlayer == currPlayer) { // you cant attack yourself
		printf("You cannot attack yourself please enter a valid number: "); // prompt
		scanf("%d",&defenderPlayer); // read user input
	}

	a = player[currPlayer].row;  // takes the row and column of the player attacking
	b = player[currPlayer].column;

	c = player[defenderPlayer].row; // takes the row and column of player defending
	d = player[defenderPlayer].column;

	z = abs(c-a);
	z = z+abs(d-b);   // gets the distance between the two

	if (attackType == NEAR && z <= 1 ) { // only performed on player on the same slot or 1 away.
		printf("You have chosen near attack");

		if(player[defenderPlayer].strength <= 70)   // if the defender strength points is less than or equal to 70
		{
			player[defenderPlayer].lifePoints -= 0.5 * player[currPlayer].strength; // reduce defender lifePoints
			if (player[defenderPlayer].lifePoints < 0)
			{
				printf("player %d lost!\n", defenderPlayer);
				playerQuit(defenderPlayer, &playerNumber, upLeft, upRight, downLeft, downRight); // remove player from game
			}
		}
		else if(player[defenderPlayer].strength > 70)  // if the defender points is greater than 70
		{
			player[currPlayer].lifePoints -= 0.3 * player[defenderPlayer].strength; // reduce defender lifePoints
			if (player[currPlayer].lifePoints <= 0) // if players life points less than or equal to zero
			{
				printf("player %d lost!\n", currPlayer);
				playerQuit(currPlayer, &playerNumber, upLeft, upRight, downLeft, downRight); // remove player from game
			}
		}
	}
	else if (attackType == NEAR && z > 1)
	{
		 printf("You can't attack, the player must be on the same slot or one slot away for a near attack\n");
		 attack(currPlayer, playerNumber, upLeft, upRight, downLeft, downRight);
	}

	if (attackType == DISTANT && z > 1 && z < 5) // only performed against players who are a distance 2-4 slots away
	{
		printf("You have chosen distant attack\n");

		if(player[currPlayer].dexterity > player[defenderPlayer].dexterity) // if the attacker dexterity is greater than the defending player
		{
			player[defenderPlayer].lifePoints -= 0.3 * player[currPlayer].strength; // reduce defender lifePoints
			if (player[defenderPlayer].lifePoints < 0)
			{
				printf("player %d lost!\n", defenderPlayer);
				playerQuit(defenderPlayer, &playerNumber, upLeft, upRight, downLeft, downRight); // remove player from game
			}
		}
	}
	else if (attackType == DISTANT && (z <= 1 || z >= 5)) // if
	{
	 printf("The player must be 2-4 slots away in order to perform a distant attack\n");
	 attack(currPlayer, playerNumber, upLeft, upRight, downLeft, downRight);
	}

	if (attackType == MAGIC && (player[currPlayer].smartness + player[currPlayer].magicSkills > 150)) {
		printf("You have chosen magic attack\n");
		player[defenderPlayer].lifePoints -= ((0.5* player[currPlayer].magicSkills) + (0.2 * player[currPlayer].smartness));
		if (player[defenderPlayer].lifePoints < 0)
		{
			printf("player %d lost!\n", defenderPlayer);
			playerQuit(defenderPlayer, &playerNumber, upLeft, upRight, downLeft, downRight); // remove player from game
		}
	} else if (attackType == MAGIC && (player[currPlayer].smartness + player[currPlayer].magicSkills <= 150)) {
		printf("You do not meet the requirements to perform a magic attack\n");
		attack(currPlayer, playerNumber, upLeft, upRight, downLeft, downRight);
	}
}
