/*
 * operations.h
 *
 *  Created on: 6 Apr 2017
 *      Author: james
 */
#ifndef OPERATIONS_H_
#define OPERATIONS_H_

#endif /* OPERATIONS_H_ */

#define BOARD_SIZE 7
#define REQ_DISTANCE 3

// Definition of boolean types This avoids using <stdbool.h>
typedef int bool;
enum { false, true };

typedef enum playerTypes {ELF, HUMAN, OGRE, WIZARD} playerTypes; // enumeration for the type of player
enum slotTypes {CITY, HILL, LEVEL_GROUND} slotTypes; // enumeration for the type of slot
enum playerActions {ATTACK, MOVE} playerActions; // enumeration for the type of slot

// The slot template

struct slot{
	int row; //row number
	int column; //column number

	struct slot *left; // adjacent left slot
	struct slot *right; // adjacent right slot
	struct slot *up; // adjacent up slot
	struct slot *down; // adjacent down slot

	enum slotTypes type; // enum slotTypes called slotType
	int player; // integer variable to indicate which player is in the slot if there is a player in the slot
};

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
void slotInitialize(struct slot **upLeft);
