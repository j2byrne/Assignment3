/*
 * startOperations.c
 *
 *  Created on: 10 Apr 2017
 *      Author: james
 */

#include <stdio.h>
#include <stdlib.h>
#include "operations.h"

void createBoard(int boardSize, struct slot **upLeft, struct slot **upRight, struct slot **downLeft, struct slot **downRight){

	//The board is represented as a pointer of pointer to slots
	//This allocates in memory the space for the pointers to each row of the board
	struct slot ** board = malloc(boardSize * sizeof(struct slot *));

	for(int i = 0; i < boardSize; i++){
		//This allocates in memory the space for the slots in each row of the board
		board[i] = malloc(boardSize * sizeof(struct slot));

		//For each slot it sets up the row and column number
		for(int j=0;j < boardSize; j++){
			board[i][j].row = i;
			board[i][j].column = j;
		}
	}

	//It sets up the adjacent slots for the slots that are
	//not at the borders. These slots have 4 adjacent elements
	for(int i = 1; i < boardSize-1; i++){
		for(int j=1;j < boardSize-1; j++){
			board[i][j].up = &board[i-1][j];
			board[i][j].right = &board[i][j+1];
			board[i][j].down = &board[i+1][j];
			board[i][j].left = &board[i][j-1];
		}
	}

	//It sets up the adjacent slots for the slots that are
	//in the first and the last row, except the slots at the edges.
	for(int j = 1; j < boardSize -1; j++) {
		//It sets up the adjacent slots for the slots that are in the first row.
		//These slots don't have an adjacent element on top of them
		// because they are on the first row of the board
		board[0][j].right = &board[0][j+1];
		board[0][j].left = &board[0][j-1];
		board[0][j].down = &board[1][j];
		board[0][j].up = NULL;

		//It sets up the adjacent slots for the slots that are in the last row.
		//These slots don't have an adjacent element on down them
		// because they are on the last row of the board
		board[boardSize - 1][j].right = &board[boardSize - 1][j+1];
		board[boardSize -1][j].left = &board[boardSize - 1][j-1];
		board[boardSize - 1][j].up = &board[boardSize - 2][j];
		board[boardSize - 1][j].down = NULL;
	}

	//It sets up the adjacent slots for the slots that are
	//in the first and the last column, except the slots at the edges.
	for(int i = 1; i < boardSize -1; i++){
		//It sets up the adjacent slots for the slots that are in the first column.
		//These slots don't have an adjacent element on the left
		// because they are on the first column of the board
		board[i][0].right = &board[i][1];
		board[i][0].up = &board[i-1][0];
		board[i][0].down = &board[i+1][0];
		board[i][0].left = NULL;

		//It sets up the adjacent slots for the slots that are in the last column.
		//These slots don't have an adjacent element on the right
		// because they are on the last column of the board
		board[i][boardSize-1].left = &board[i][boardSize-2];
		board[i][boardSize -1].up = &board[i -1][boardSize-1];
		board[i][boardSize -1].down = &board[i+1][boardSize -1];
		board[i][boardSize -1].right = NULL;
	}

	//It sets up the adjacent slots for the slot at position (0,0).
	//This only has only 2 adjacent slots: right and down
	board[0][0].right = &board[0][1];
	board[0][0].down = &board[1][0];

	//It sets up the adjacent slots for the slot at position (0,boardSize -1).
	//This only has only 2 adjacent slots: left and down
	board[0][boardSize-1].left = &board[0][boardSize-2];
	board[0][boardSize -1].down = &board[1][boardSize -1];

	//It sets up the adjacent slots for the slot at position (boarSize -1 ,0).
	//This only has only 2 adjacent slots: up and right
	board[boardSize -1][0].right = &board[boardSize -1][1];
	board[boardSize -1][0].up = &board[boardSize -2][0];

	//It sets up the adjacent slots for the slot at position (boarSize -1 ,boardSize-1).
	//This only has only 2 adjacent slots: up and left
	board[boardSize - 1][boardSize-1].up = &board[boardSize-2][boardSize-1];
	board[boardSize - 1][boardSize -1].left = &board[boardSize -1][boardSize -2];

	//assigns a pointer to slot at position (0, 0)
	*upLeft = &board[0][0];
	//assigns pointer of pointer to slot at position (0, boardSize -1)
	*upRight = &board[0][boardSize -1];
	//assigns pointer of pointer to slot at position ( boardSize -1,)
	*downLeft = &board[boardSize -1][0];
	//assigns pointer of pointer to slot at position (boardSize -1, boardSize -1)
	*downRight = &board[boardSize -1][boardSize -1];
}

void slotInitialize(struct slot **currSlot)
{
	struct slot **nextRowSlot = NULL; // pointer to the first slot pointer on the next row

	for (size_t i = 0; i < BOARD_SIZE; i++) // looping through slot rows
	{
		nextRowSlot = &((*currSlot)->down); // assigning the slot pointer down from currSlot to newRowSlot

		for (size_t j = 0; j < BOARD_SIZE; j++) // looping through slot columns
		{
			for (size_t k = 0; k < 6; k++)
			{
				(*currSlot)->playersInSlot[k] = false;
			}
			(*currSlot)->type = rand()%3; // assigning the slot a type
			currSlot = &(*currSlot)->right; // assign the next slot to currSlot
		}

		currSlot = nextRowSlot; // assign nextRowSlot to currSlot
	}
}

void printBoard(struct slot **currSlot, int playerNumber) {
	struct slot **nextRowSlot = NULL; // pointer to the first slot pointer on the next row

	char *slotType[3] = {" C  "," H  ", " LG "}; // array of slot type names

	printf("|"); // print newline
	for (size_t i = 0; i < BOARD_SIZE; i++) // print newline
	{
			printf("----|"); // print border
	}
	printf("\n"); // print newline

	for (size_t i = 0; i < BOARD_SIZE; i++) // looping through slot rows
	{
		nextRowSlot = &((*currSlot)->down); // assigning the slot pointer down from currSlot to newRowSlot

		printf("|"); // print border

		for (size_t j = 0; j < BOARD_SIZE; j++) // looping through slot columns
		{
			printf("%s|", slotType[(*currSlot)->type]); // print slot type

			currSlot = &(*currSlot)->right; // assign the next slot to currSlot
		}
		printf("\n"); // print newline
		printf("|"); // print border
		for (size_t i = 0; i < BOARD_SIZE; i++) // print border per slot
		{
				printf("----|"); // print border
		}
		printf("\n"); // print newline

		currSlot = nextRowSlot; // assign nextRowSlot to currSlot
	}
}

void playerInitialize(int *playerNumber)
{
	printf("Please enter the number of players (2-6): ");
	scanf(" %d", &(*playerNumber));
	fflush(stdin);

	for (int currentPlayer = 0; currentPlayer < *playerNumber; currentPlayer++) // loop through players
	{
		printf("Please input player %ds name: ", currentPlayer+1); // prompt
		scanf(" %19[^\n]s", player[currentPlayer].name); // read player name
		fflush(stdin); // flush the standard input

		// check if player type input from user is valid and if not request to give another input that is valid
		do
		{
			printf("Please input the player type, 0 for Elf, 1 for Human, 2 for Ogre and 3 for Wizard: ");
			scanf("%d", &player[currentPlayer].type); // read player type from user and assign data to player structure
			getchar(); // read newline character from buffer for fgets
		} while (player[currentPlayer].type > 3); // check to see if input is valid

		puts(""); // newline

		player[currentPlayer].lifePoints = 100; // set lifePoints to 100

		// calling function depending on the player type
		switch (player[currentPlayer].type)
		{
			case ELF: // if player is an elf
				player[currentPlayer].luck = 60 + rand()%41; // set player luck to between 60 and 100
				player[currentPlayer].smartness = 70 + rand()%31; // set player smartness to between 70 and 100
				player[currentPlayer].strength = 1 + rand()%50; // set player luck to between 1 and 50
				player[currentPlayer].magicSkills = 51 + rand()%29; // set player luck to between 51 and 80
				player[currentPlayer].dexterity = 1 + rand()%100; // set player luck to between 1 and 100
				break;
			case HUMAN: // if player is an human
				do {
					player[currentPlayer].magicSkills=1+rand()%100; // set player luck to between 60 and 100
					player[currentPlayer].smartness = 1+rand()%100; // set player luck to between 60 and 100
					player[currentPlayer].strength = 1+rand()%100; // set player luck to between 60 and 100
					player[currentPlayer].luck= 1+rand()%100; // set player luck to between 60 and 100
					player[currentPlayer].dexterity= 1+rand()%100; // set player luck to between 60 and 100
				} while((player[currentPlayer].magicSkills + player[currentPlayer].smartness + player[currentPlayer].strength + player[currentPlayer].luck + player[currentPlayer].dexterity) >= 300);
				break;
			case OGRE: // if player is an ogre
				do{
					player[currentPlayer].smartness  = rand()%21; // set player luck to between 60 and 100
					player[currentPlayer].luck = rand()%51; // set player luck to between 60 and 100
				} while((player[currentPlayer].smartness + player[currentPlayer].luck) > 50);

				player[currentPlayer].magicSkills = 0; // set player luck to between 60 and 100
				player[currentPlayer].strength = 80 + rand()%21; // set player luck to between 60 and 100
				player[currentPlayer].dexterity = 80 + rand()%21; // set player luck to between 60 and 100
				break;
			case WIZARD: // if player is an wizard
			    player[currentPlayer].magicSkills = 80 + rand()%21; // set player luck to between 60 and 100
				player[currentPlayer].smartness = 90 + rand()%11; // set player luck to between 60 and 100
				player[currentPlayer].strength = 1 + rand()%21; // set player luck to between 60 and 100
				player[currentPlayer].dexterity= 1 + rand()%100; // set player luck to between 60 and 100
			    player[currentPlayer].luck = 50+ rand()%51; // set player luck to between 60 and 100
				break;
			default:
				break;
		}
	}
}

void printPlayers(int playerNumber) {
	printf("%20s %10s %4s %9s %8s %11s %4s %9s %8s\n", "name", "LifePoints", "Type", "Smartness", "Strength", "magicSkills", "Luck", "Dexterity", "Position"); // print header
	for (int currentPlayer = 0; currentPlayer < playerNumber; currentPlayer++) // loop through players
	{
		printf("%20s %10d %4d %9d %8d %11d %4d %9d (%d,%d)\n", player[currentPlayer].name, player[currentPlayer].lifePoints, player[currentPlayer].type, player[currentPlayer].smartness, player[currentPlayer].strength, player[currentPlayer].magicSkills, player[currentPlayer].luck, player[currentPlayer].dexterity, player[currentPlayer].row, player[currentPlayer].column); // printing player information
	}
}

