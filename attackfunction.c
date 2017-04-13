#include <stdio.h>
#include <stdlib.h>
#include "operations.h"

void attack( int currPlayer,int playerNumber)
{
 int attackType;
 int defenderName;
 int z,a,b,c,d,i;

printf("You have decided to attack"); // The current player has choosen to attack this round 
printf("0 for near attack \n1 for distant attack \n2 for magic attack"); // player decides which attack to use 
scanf("%d",&attackType);

printf("Enter the name of the player you wish to attack out of the following list"); 

for (i= 0; i < playerNumber; i++)
{
printf("Do you want to attack player %d",i);
}

scanf("%d",&defenderName);

a = player[currPlayer].row;
b = player[currPlayer].column;

c = player[defenderName].row;
d = player[defenderName].column;

z=abs(a-b);
z=z+abs(c-d);

if (attackType == 0 && z >=1 ) {                   // only performed on player on the same slot or 1 away.
	printf("You have choosen near attack"); 
	
	
	       if(player[currPlayer].strength <= 70)   // if the attacker strength points is less than or equal to 70
		   {			   
		       player[defenderName].lifePoints -= 0.5 * player[currPlayer].strength; // reduce defender lifePoints
	          }
	             else if(player[currPlayer].strength > 70)  // if the attacker points is greater than 70
				 {
		           player[defenderName].lifePoints -= 0.3 * player[currPlayer].strength; // reduce defender lifePoints
                 }
         }

		 
		 else if (attackType==0 && z<1)
		 {
			   printf("The player must be on the same slot or one slot away for a near attack");
		 }

		 
if(attackType == 1 && 1 < z > 5) // only performed against players who are a distance greater 2-4 away
        {  
	    printf("You have choosen distant attack");
	
           if(player[currPlayer].dexterity > player[defenderName].dexterity) // if the playerAttacked dexterity is greater than the attacking player
		   {
		      player[defenderName].lifePoints -= 0.3 * player[currPlayer].strength; // reduce attacker lifePoints
		   }
	         else if (player[currPlayer].dexterity <= player[defenderName].dexterity) // if the attacker points is greater than 70
			 {
				 player[defenderName].lifePoints = player[defenderName].lifePoints;
             }
         }
		 else if (attackType=1 && z>=1 || z<=5)
			 printf("The player must be 2-4 slots away in order to perform a distant attack");

if(attackType == 2 && player[currPlayer].smartness + player[currPlayer].magicSkills >150){
	      printf("You have choosen magic attack");
          player[defenderName].lifePoints -= ((0.5* player[currPlayer].magicSkills) + (0.2 * player[currPlayer].smartness)); 
}
	
	else if (attackType == 2 && player[currPlayer].smartness + player[currPlayer].magicSkills <=150){
		printf("You do not meet the requirements to perform a magic attack");
	}
	
}
