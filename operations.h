/*
 * operations.h
 *
 *  Created on: 10 Apr 2017
 *      Author: james
 */

#ifndef OPERATIONS_H_
#define OPERATIONS_H_

#define BOARD_SIZE 4
#define REQ_DISTANCE 3

// Definition of boolean types gave errors on eclispe, hence using stdbool.h
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

enum playerTypes {ELF, HUMAN, OGRE, WIZARD}; // enumeration for the type of player
enum slotTypes {CITY, HILL, LEVEL_GROUND}; // enumeration for the type of slot
enum playerActions {ATTACK, MOVE, QUIT};  // enumeration for the type of move the player will make
enum attackTypes {NEAR, DISTANT, MAGIC}; //enumeration for the type of attack the player will make
enum movePositions { UP, RIGHT, DOWN, LEFT}; // enumeration for slot the player wants to move relative to their slot

struct playersInSlot { // linked list to store players in a slot
	struct players *player;
	struct playersInSlot *next;
};

// The slot template
struct slot{
	int row; //row number
	int column; //column number

	struct slot *left; // adjacent left slot
	struct slot *right; // adjacent right slot
	struct slot *up; // adjacent up slot
	struct slot *down; // adjacent down slot

	enum slotTypes type; // enum slotTypes called slotType
	bool playersInSlot[6];
};

struct players
{
	char name[20]; // user name
	enum playerTypes type; // enum playerTypes called playerType

	int lifePoints; // lifepoints the player has
	int position;

	// player capabilities
	int smartness;
	int strength;
	int magicSkills;
	int luck;
	int dexterity;

	int row;
	int column;
};

struct players player[6];

// Function Prototypes

/*
* This function creates the board
* Parameters:
* 	boardSize: the size of the board
* 	upLeft: pointer of pointer to slot at position (0, 0)
* 	upRight: pointer of pointer to slot at position (0, size -1)
* 	downLeft: pointer of pointer to slot at position (size -1, 0)
* 	upLeft: pointer of pointer to slot at position (size - 1, size -1)
*/

void createBoard(int board_size, struct slot **upLeft, struct slot **upRight, struct slot **downLeft, struct slot **downRight);
void slotInitialize(struct slot **currSlot);
void printBoard(struct slot **currSlot, int playerNumber);
void playerInitialize(int *playerNumber);
void printPlayers(int playerNumber);
void playerPositionStart(int currPlayer, int row, int column, struct slot **upLeft, struct slot **upRight, struct slot **downLeft, struct slot **downRight);

void playerAttack(int currPlayer, struct slot **upLeft, struct slot **upRight, struct slot **downLeft, struct slot **downRight);
void playerMove(int currPlayer, struct slot *currSlot, int row, int column);
struct slot * findSlot(int row, int column, struct slot **upLeft, struct slot **upRight, struct slot **downLeft, struct slot **downRight);


#endif /* OPERATIONS_H_ */

