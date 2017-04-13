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
}

struct slot * findSlot(int row, int column, struct slot **upLeft, struct slot **upRight, struct slot **downLeft, struct slot **downRight) {
	struct slot * currSlot = malloc(sizeof(struct slot));

	// player[currPlayer].row = 5;

	if (row >= BOARD_SIZE/2)
	{
		if (column >= BOARD_SIZE/2)
		{
			currSlot = *downRight;
		}
		else
		{
			currSlot = *upRight;
		}
	}
	else
	{
		if (column >= BOARD_SIZE/2)
		{
			currSlot = *downLeft;
		}
		else
		{
			currSlot = *upLeft;
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

	return currSlot;
}
