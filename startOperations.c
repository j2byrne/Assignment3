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
			(*currSlot)->type = rand()%3; // assigning the slot a type
			currSlot = &(*currSlot)->right; // assign the next slot to currSlot
		}

		currSlot = nextRowSlot; // assign nextRowSlot to currSlot
	}
}

void printBoard(struct slot **currSlot) {
	struct slot **nextRowSlot = NULL; // pointer to the first slot pointer on the next row

	for (size_t i = 0; i < BOARD_SIZE; i++) // looping through slot rows
	{
		nextRowSlot = &((*currSlot)->down); // assigning the slot pointer down from currSlot to newRowSlot

		for (size_t j = 0; j < BOARD_SIZE; j++) // looping through slot columns
		{
			printf("(%d,%d) %d\t", (*currSlot)->column, (*currSlot)->row, (*currSlot)->type);
			currSlot = &(*currSlot)->right; // assign the next slot to currSlot
		}
		printf("\n");

		currSlot = nextRowSlot; // assign nextRowSlot to currSlot
	}
}

void playerInitialize(struct players **playerPtr, int *playerNumber)
{
	do
	{
		printf("Please enter the number of players (2-6): "); // prompt
		scanf(" %d", playerNumber); // read the number of players from the user
		getchar(); // read newline character from buffer (for fgets in playerInitialize)
	} while (*playerNumber > 6 || *playerNumber < 2); // validate that it is between 1 and 6

	*playerPtr = (struct players *)calloc(*playerNumber, sizeof(struct players));

	for (int currentPlayer = 0; currentPlayer < *playerNumber; currentPlayer++)
	{
		printf("Please input player %ds name: ", currentPlayer+1); // prompt
		scanf("%19[^\n]s", (*playerPtr + currentPlayer)->name);

		// check if player type input from user is valid and if not request to give another input that is valid
		do
		{
			printf("Please input the player type, 0 for Elf, 1 for Human, 2 for Ogre and 3 for Wizard: ");
			scanf("%d", &(*playerPtr +currentPlayer)->type); // read player type from user and assign data to player structure
			fflush(stdin); // flush buffer
		} while ((*playerPtr +currentPlayer)->type > 3);

		(*playerPtr +currentPlayer)->lifePoints = 100; // set lifePoints to 100

		// calling function depending on the player type
		switch ((*playerPtr +currentPlayer)->type)
		{
			case ELF: // if player is an elf
				(*playerPtr +currentPlayer)->luck = 60 + rand()%41; // set player luck to between 60 and 100
				(*playerPtr +currentPlayer)->smartness = 70 + rand()%31; // set player smartness to between 70 and 100
				(*playerPtr +currentPlayer)->strength = 1 + rand()%50; // set player luck to between 1 and 50
				(*playerPtr +currentPlayer)->magicSkills = 51 + rand()%29; // set player luck to between 51 and 80
				(*playerPtr +currentPlayer)->dexterity = 1 + rand()%100; // set player luck to between 1 and 100
				break;
			case HUMAN: // if player is an human
				do {
					(*playerPtr +currentPlayer)->magicSkills=1+rand()%100; // set player luck to between 60 and 100
					(*playerPtr +currentPlayer)->smartness = 1+rand()%100; // set player luck to between 60 and 100
					(*playerPtr +currentPlayer)->strength = 1+rand()%100; // set player luck to between 60 and 100
					(*playerPtr +currentPlayer)->luck= 1+rand()%100; // set player luck to between 60 and 100
					(*playerPtr +currentPlayer)->dexterity= 1+rand()%100; // set player luck to between 60 and 100
				} while(((*playerPtr +currentPlayer)->magicSkills + (*playerPtr +currentPlayer)->smartness + (*playerPtr +currentPlayer)->strength + (*playerPtr +currentPlayer)->luck + (*playerPtr +currentPlayer)->dexterity) >= 300);
				break;
			case OGRE: // if player is an ogre
				do{
					(*playerPtr +currentPlayer)->smartness  = rand()%21; // set player luck to between 60 and 100
					(*playerPtr +currentPlayer)->luck = rand()%51; // set player luck to between 60 and 100
				} while(((*playerPtr +currentPlayer)->smartness + (*playerPtr +currentPlayer)->luck) > 50);

				(*playerPtr +currentPlayer)->magicSkills = 0; // set player luck to between 60 and 100
				(*playerPtr +currentPlayer)->strength = 80 + rand()%21; // set player luck to between 60 and 100
				(*playerPtr +currentPlayer)->dexterity = 80 + rand()%21; // set player luck to between 60 and 100
				break;
			case WIZARD: // if player is an wizard
			    (*playerPtr +currentPlayer)->magicSkills = 80 + rand()%21; // set player luck to between 60 and 100
				(*playerPtr +currentPlayer)->smartness = 90 + rand()%11; // set player luck to between 60 and 100
				(*playerPtr +currentPlayer)->strength = 1 + rand()%21; // set player luck to between 60 and 100
				(*playerPtr +currentPlayer)->dexterity= 1 + rand()%100; // set player luck to between 60 and 100
			    (*playerPtr +currentPlayer)->luck = 50+ rand()%51; // set player luck to between 60 and 100
				break;
			default:
				break;
		}
	}
}

void printPlayers(struct players **playerPtr, int *playerNumber) {
	printf("%20s %10s %4s %9s %8s %11s %4s %9s\n", "name", "LifePoints", "Type", "Smartness", "Strength", "magicSkills", "Luck", "Dexterity");
	for (int currentPlayer = 0; currentPlayer < *playerNumber; currentPlayer++)
	{
		printf("%20s %10d %4d %9d %8d %11d %4d %9d\n", (*playerPtr)->name, (*playerPtr)->lifePoints, (*playerPtr)->type, (*playerPtr)->smartness, (*playerPtr)->strength, (*playerPtr)->magicSkills, (*playerPtr)->luck, (*playerPtr)->dexterity);
	}
}
