/*
 * moveOperations.h
 *
 *  Created on: 9 Apr 2017
 *      Author: james
 */

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "operations.h"

void playerTurn(int currPlayer, int playerNumber, struct slot **upLeft, struct slot **upRight, struct slot **downLeft, struct slot **downRight) {
	enum playerActions playerAction; // enum playerActions to store what the player is going to do
	struct slot * currSlot;
	int row, column;

	printf("Player %d enter 0 if you want to attack or 1 if you want to move or 2 to quit the game: ", currPlayer+1); // prompt
	scanf("%d", &playerAction); // read integer which is saved in the enumeration playerAction to determine whether the player wants to attack another player or move position

	// switch to determine the players action
	switch (playerAction)
	{
		case ATTACK: // case for when player wants to attack
			attack(currPlayer, playerNumber, upLeft, upRight, downLeft, downRight);
			break;
		case MOVE: // case for when player wants to move position
			row = player[currPlayer].row;
			column = player[currPlayer].column;
			currSlot = findSlot(row, column, upLeft, upRight, downLeft, downRight);
			playerMove(currPlayer, currSlot, row, column); // call playerMove function
			break;
		case QUIT: // case for when player wants to quit the game
			printf("Player %d has quit the game\n", currPlayer+1);
			playerQuit(currPlayer, playerNumber, upLeft, upRight, downLeft, downRight);
			break;
		default:
			break;
	}
	puts(""); // print newline
	printPlayers(playerNumber); // print player info.
	puts(""); // print newline
}

void playerMove(int currPlayer, struct slot *currSlot, int row, int column) {
	enum movePositions position;
	struct slot * newSlot;
	bool slotEdge[4]; // bool to see whick slots the player can move to in the oder of up, right, down, left
	char *slots[4] = {"up", "right", "down", "left"};

	for (int i = 0; i < 4; i++)
	{
		slotEdge[i] = true;
	}
	if (currSlot->up == NULL) {
		slotEdge[0] = false;
	}
	if (currSlot->right == NULL) {
		slotEdge[1] = false;
	}
	if (currSlot->down == NULL) {
		slotEdge[2] = false;
	}
	if (currSlot->left == NULL) {
		slotEdge[3] = false;
	}

	printf("Enter the slot you want to move to, "); // prompt
	for (int i = 0; i < 4; i++)
	{
		if (slotEdge[i] == true)
			printf("%d for %s ", i, slots[i]);
	}
	printf(": ");
	scanf("%d", &position);

	while (slotEdge[position] == false)
	{
		printf("Please enter a valid entry: ");
		scanf("%d", &position);
	}

	switch(position)
	{
		case 0:
			newSlot = currSlot->up;
			row--;
			break;
		case 1:
			newSlot = currSlot->right;
			column++;
			break;
		case 2:
			newSlot = currSlot->down;
			row++;
			break;
		case 3:
			newSlot = currSlot->left;
			column--;
			break;
		default:
			break;
	}

	currSlot->playersInSlot[currPlayer] = false;
	newSlot->playersInSlot[currPlayer] = true;

	player[currPlayer].row = row;
	player[currPlayer].column = column;

	switch (newSlot[currPlayer].type)
	{
		case CITY: // if player moved to a city
			if (player[currPlayer].smartness > 60) // if current players smartness is greater than 60
			{
				player[currPlayer].magicSkills += 10; // add 10 to players magic skills
				if (player[currPlayer].magicSkills > 100) // if player magic skills is greater to 100 set magic skills to 100
					player[currPlayer].magicSkills = 100;
			}
			else if (player[currPlayer].smartness <= 50)// if current players smartness is less than or equal to 50
			{
				player[currPlayer].dexterity -= 10;// subtract 10 from players dexterity
				if (player[currPlayer].dexterity < 0)// if player dexterity is less  than 0 set player dexterity to 0
					player[currPlayer].dexterity = 0;
			}
			break;
		case HILL:
			if (player[currPlayer].dexterity >= 60) // if current players dexterity is greater than 60
				{
					player[currPlayer].strength += 10; // add 10 to players strength
					if (player[currPlayer].strength > 100) // if player strength is greater to 100 set strength to 100
						player[currPlayer].strength = 100;
				}
				else if (player[currPlayer].dexterity < 50)// if current players dexterity is less than or equal to 50
				{
					player[currPlayer].strength -= 10;// subtract 10 from players dexterity
					if (player[currPlayer].strength < 0)// if player dexterity is less  than 0 set player strength to 0
						player[currPlayer].strength = 0;
				}
			break;
		// note there are no changes to player capabilities if the slot is a level ground
		default:
			break;
	}
}

struct slot * findSlot(int row, int column, struct slot **upLeft, struct slot **upRight, struct slot **downLeft, struct slot **downRight) {
	struct slot * currSlot = malloc(sizeof(struct slot));

	if (row >= BOARD_SIZE/2) // if on the right side of the board
		{
			if (column >= BOARD_SIZE/2) // if on bottom of the board
			{
				currSlot = *downRight; // assign bottom right corner pointer to currSlot
			}
			else // if on the top of the board
			{
				currSlot = *upRight; // assign top right corner pointer to currSlot
			}
		}
		else // if on the left side of the board
		{
			if (column >= BOARD_SIZE/2) // if on bottom of the board
			{
				currSlot = *downLeft; // assign bottom left corner pointer to currSlot
			}
			else // if on the top of the board
			{
				currSlot = *upLeft; // assign top right corner pointer to currSlot
			}
		}

	bool found = false; // if the slot hasn't been found

	//while the slot is not found
	while(found == false) {

		//if the row of the current slot is > of the row of the desired slot, we move up
		if(currSlot->row > row) {

			//the current slot now points to the slot one row up
			currSlot = currSlot->up;
		}
		//if the row of the current slot is < of the row of the desired slot, we move down
		if(currSlot->row < row) {

			//the current slot now points to the slot one row down
			currSlot = currSlot->down;
		}
		//if the column of the current slot is > of the column of the desired slot, we move left
		if(currSlot->column > column) {

			//the current slot now points to the slot one column left
			currSlot = currSlot->left;
		}
		//if the column of the current slot is < of the column of the desired slot, we move right
		if(currSlot->column < column) {

			//the current slot now points to the slot one column right
			currSlot = currSlot->right;
		}
		//if the current slot is at a column and a row equal to the desired column and row, respectively we found the slot
		if(currSlot->column == column && currSlot->row == row) {
			found = true;
		}
	} // end of while loop

	return currSlot; // return currSlot
}

void playerQuit(int currPlayer, int playerNumber, struct slot **upLeft, struct slot **upRight, struct slot **downLeft, struct slot **downRight) {
	struct slot * playerSlot; // slot of player
	int row = player[currPlayer].row; // row of player position
	int column = player[currPlayer].column; // column of player position

	playerSlot = findSlot(row, column, upLeft, upRight, downLeft, downRight); // return pointer to the slot that the player is in

	playerSlot->playersInSlot[currPlayer] = false; // set that the player isnt in the slot

	player[currPlayer].lifePoints = 0; // set players lifePoints to 0

	playersInGame--; // decrement PlayersInGame
}

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
				playerQuit(defenderPlayer, playerNumber, upLeft, upRight, downLeft, downRight); // remove player from game
			}
		}
		else if(player[defenderPlayer].strength > 70)  // if the defender points is greater than 70
		{
			player[currPlayer].lifePoints -= 0.3 * player[defenderPlayer].strength; // reduce defender lifePoints
			if (player[currPlayer].lifePoints <= 0) // if players life points less than or equal to zero
			{
				printf("player %d lost!\n", currPlayer);
				playerQuit(currPlayer, playerNumber, upLeft, upRight, downLeft, downRight); // remove player from game
			}
		}
	}
	else if (attackType == NEAR && z > 1)
	{
		 printf("You can't attack, the player must be on the same slot or one slot away for a near attack\n");
		 playerTurn(currPlayer, playerNumber, upLeft, upRight, downLeft, downRight);
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
				playerQuit(defenderPlayer, playerNumber, upLeft, upRight, downLeft, downRight); // remove player from game
			}
		}
	}
	else if (attackType == DISTANT && (z <= 1 || z >= 5)) // if
	{
	 printf("The player must be 2-4 slots away in order to perform a distant attack\n");
	 playerTurn(currPlayer, playerNumber, upLeft, upRight, downLeft, downRight);
	}

	if (attackType == MAGIC && (player[currPlayer].smartness + player[currPlayer].magicSkills > 150)) {
		printf("You have chosen magic attack\n");
		player[defenderPlayer].lifePoints -= ((0.5* player[currPlayer].magicSkills) + (0.2 * player[currPlayer].smartness));
		if (player[defenderPlayer].lifePoints < 0)
		{
			printf("player %d lost!\n", defenderPlayer);
			playerQuit(defenderPlayer, playerNumber, upLeft, upRight, downLeft, downRight); // remove player from game
		}
	} else if (attackType == MAGIC && (player[currPlayer].smartness + player[currPlayer].magicSkills <= 150)) {
		printf("You do not meet the requirements to perform a magic attack\n");
		playerTurn(currPlayer, playerNumber, upLeft, upRight, downLeft, downRight);
	}
}

