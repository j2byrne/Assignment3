#include <stdio.h>
#include "crossfireOperations.h"

void attack(struct players player[], int currentPlayer)
{
 int attackType;
 int defenderName;

printf("You have decided to attack"); // The current player has choosen to attack this round 
printf("0 for near attack \n1 for distant attack \n2 for magic attack"); // player decides which attack to use 
scanf("%d",&attackType);

printf("Enter the name of the player you wish to attack out of the following list"); 

for (int currentPlayer = 0; currentPlayer < playerNumber; currentPlayer++)
{

 printPlayers(player);            // loop to print player names 
}
 
scanf("%d",&defenderNameame);

if (attackType == 0 && Distance >2) {                   // only performed on player on the same slot or 1 away.
	printf("You have choosen near attack"); 
	
	       if {
		      (player[currentPlayer].strength <= 70) // if the attacker strength points is less than or equal to 70
		       player[defenderName].lifePoints -= 0.5 * player[currentPlayer].strength; // reduce defender lifePoints
	          }
	             else if {
			             (player[currentPlayer].strength > 70)  // if the attacker points is greater than 70
		                  player[defenderName].lifePoints -= 0.3 * player[currentPlayer].strength; // reduce defender lifePoints
                         }
         }
		 
		 else if{
		       (attackType==0 && /*requirements arent met*/)
			   printf("The player must be on the same slot or one slot away for a near attack");
		 }

		 
if(attackType == 1 && 1 < Distance> 5){  // only performed against players who are a distance greater 2-4 away
	    printf("You have choosen distant attack");
	
           if{
			 (player[currentPlayer].dexterity > player[defenderName]) // if the playerAttacked dexterity is greater than the attacking player
		      player[defenderName].lifePoints -= 0.3 * player[currentPlayer].strength; // reduce attacker lifePoints
		   }
	         else if {
				     (player[currentPlayer].dexterity <= player[defenderName]) // if the attacker points is greater than 70
		             player[defenderName].lifePoints = player[defenderName].lifepoints
                     }
         }
		 else if (k=1 && /*requirements arent met*/)
			 printf("The player must be 2-4 slots away in order to perform a distant attack")

if(attackType == 2 && player[currentPlayer].smartness + player[currentPlayer].magicskills >150){
	      printf("You have choosen magic attack");
          player[defenderName].lifepoints -= ((0.5* player[currentPlayer].magicskills) + (0.2 * player[currentPlayer].smartness)); 
}
	
	else if (attackType == 2 && player[currentPlayer].smartness + player[currentPlayer].magicskills <=150){
		printf("You do not meet the requirements to perform a magic attack");
	}
	
}