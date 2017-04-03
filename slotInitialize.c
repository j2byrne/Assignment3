#include <stdlib.h>
#include "operations.h" // operations header

void slotInitialize(struct slots slot[])
{
	// loop though each slot
	for (size_t currentSlot = 0; currentSlot < slotNumber-1; currentSlot++)
	{
		slot[currentSlot].type = rand()%3; // pick a number between 0 and 2 and assign it to the enumerator called type in the currentSlot element of the slot array
		slot[currentSlot].occupied = false; // assign the occupied boolean variable to false in the currentSlot element of the array of slot array
	}
}
