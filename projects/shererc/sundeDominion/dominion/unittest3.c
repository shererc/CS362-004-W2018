/*****************************************************************
 * Name: Caleb Sherer
 * Due Date: 02/04/2018
 * File Name: unittest3.c
 * Description: Unit test for the supplyCount() function
 *****************************************************************/


#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>


int main(){

	struct gameState initGame;
	int players = 2;
	//seed doesn't really matter, we just need a working game state to see if the game is over
	int seed = 850;
	int kingdom[10] = {adventurer, smithy, cutpurse, estate, ambassador, outpost, salvager, treasure_map, mine, remodel};
	int allTestsPass = 0;
	int testPass = 0;

	int initValue = 0;
	int testValue = 0;
	initializeGame(players, kingdom, seed, &initGame);


	printf("************************************************************************\n");
	printf("***********************Testing supplyCount() Function*******************\n");
	printf("************************************************************************\n");
	int i = 0;
	int j = 0;
	// Go through each of the supply piles and make sure we get the correct number back
	for(i = 0; i < 25; i++){
		testPass = 0;
		if(initGame.supplyCount[i] != -1){
			initValue = supplyCount(i, &initGame);
			for(j = 0; j < initValue; j++){
				testValue = supplyCount(i, &initGame);
				if((initValue - j) != testValue){
					testPass = 1;
				}
				initGame.supplyCount[i] -= 1; 
			}
		}
		// Inform the user about passing the tests
		if(testPass == 1){
			printf("---ERROR--- supplyCount[%d] failed\n", i);
			allTestsPass = 1;
		} else {
			printf("---PASSED--- supplyCount[%d] passed\n",  i);
		}
	}

	if(allTestsPass == 1){
		printf("---ERROR--- supplyCount() has a problem\n");
	} else {
		printf("---ALL PASSED--- supplyCount() passed the unit test\n");
	}
	return 0;
}