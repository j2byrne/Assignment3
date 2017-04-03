#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "operations.h" // operations header

void playerInitialize(struct players player[])
{
	for (int currentPlayer = 0; currentPlayer < playerNumber; currentPlayer++)
	{
		printf("Please input player %ds name: ", currentPlayer+1); // prompt
		scanf("%19[^\n]s", player[currentPlayer].name);

		// check if player type input from user is valid and if not request to give another input that is valid
		do
		{
			printf("Please input the player type, 0 for Elf, 1 for Human, 2 for Ogre and 3 for Wizard: ");
			scanf("%d", &player[currentPlayer].type); // read player type from user and assign data to player structure
			getchar(); // read newline character from buffer for fgets
		} while (player[currentPlayer].type > 3);

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
