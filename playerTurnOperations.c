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
			break;
		case 1:
			newSlot = currSlot->right;
			break;
		case 2:
			newSlot = currSlot->down;
			break;
		case 3:
			newSlot = currSlot->left;
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

void playerQuit(int currPlayer, int *playerNumber, struct slot **upLeft, struct slot **upRight, struct slot **downLeft, struct slot **downRight) {
	struct slot * playerSlot; // slot of player
	int row = player[currPlayer].row; // row of player position
	int column = player[currPlayer].column; // column of player position

	playerSlot = findSlot(row, column, upLeft, upRight, downLeft, downRight); // return pointer to the slot that the player is in

	playerSlot->playersInSlot[currPlayer] = false; // set that the player isnt in the slot

	player[currPlayer].lifePoints = 0; // set players lifePoints to 0

	playersInGame--; // decrement PlayersInGame
}
