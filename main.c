/*
 * main.c
 *
 *  Created on: 10 Apr 2017
 *      Author: james
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "operations.h"

int main(void) {
	srand(time(NULL));
	int playerNumber;
	int winner = -1; // player number of the winner of the game

	//pointer to slot (0,0)
	struct slot *upLeft;
	//pointer to slot (0,boardSize -1)
	struct slot *upRight;
	//pointer to slot (boardSize - 1, 0)
	struct slot *downLeft;
	//pointer to slot (boardSize - 1, boardSize -1)
	struct slot *downRight;

	//Creates the board
	createBoard(BOARD_SIZE, &upLeft, &upRight, &downLeft, &downRight);

	// randomly assigns each slot a random type
	slotInitialize(&upLeft);

	playerInitialize(&playerNumber);

	for (int currPlayer = 0; currPlayer < playerNumber; currPlayer++)
	{
		int row = rand()%BOARD_SIZE;
		int column = rand()%BOARD_SIZE;

		playerPositionStart(currPlayer, row, column, &upLeft, &upRight, &downLeft, &downRight);
	}

	printBoard(&upLeft, playerNumber); // print board
	printPlayers(playerNumber);

	playersInGame = playerNumber;

	while (playersInGame > 1)
	{
		for (int currPlayer = 0; currPlayer < playerNumber && playersInGame > 1; currPlayer++)
		{
			if (player[currPlayer].lifePoints != 0)
			{
				enum playerActions playerAction; // enum playerActions to store what the player is going to do
				struct slot * currSlot;
				int row, column;

				printf("Player %d enter 0 if you want to attack or 1 if you want to move or 2 to quit the game: ", currPlayer+1); // prompt
				scanf("%d", &playerAction); // read integer which is saved in the enumeration playerAction to determine whether the player wants to attack another player or move position

				// switch to determine the players action
				switch (playerAction)
				{
					case ATTACK: // case for when player wants to attack
						attack(currPlayer, playerNumber, &upLeft, &upRight, &downLeft, &downRight);
						break;
					case MOVE: // case for when player wants to move position
						row = player[currPlayer].row;
						column = player[currPlayer].column;
						currSlot = findSlot(row, column, &upLeft, &upRight, &downLeft, &downRight);
						playerMove(currPlayer, currSlot, row, column); // call playerMove function
						break;
					case QUIT: // case for when player wants to quit the game
						printf("Player %d has quit the game\n", currPlayer+1);
						playerQuit(currPlayer, &playerNumber, &upLeft, &upRight, &downLeft, &downRight);
						break;
					default:
						break;
				}
				printBoard(&upLeft, playerNumber); // print board
				printPlayers(playerNumber);
			}
		}
	}

	for (int currPlayer = 0; currPlayer < playerNumber; currPlayer++)
	{
		if (player[currPlayer].lifePoints != 0)
		{
			winner = currPlayer;
			break;
		}
	}

	printf("Congratulations, Player %d won the game!\n", winner+1);
}


