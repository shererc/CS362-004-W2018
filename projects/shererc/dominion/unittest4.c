/*****************************************************************
 * Name: Caleb Sherer
 * Due Date: 02/04/2018
 * File Name: unittest4.c
 * Description: Unit test for the "whoseTurn()" function
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
	int testPassed = 0;
	int testValue = 0;
	initializeGame(players, kingdom, seed, &initGame);

	int allTestsPass = 0;

	int playerTurn = 0;
	int i;

	printf("**********************************************************************\n");
	printf("***********************Testing whoseTurn() Function*******************\n");
	printf("**********************************************************************\n");

	/* first test 2 players */
	for(i = 0; i < 100; i++){
		playerTurn = whoseTurn(&initGame);
		if(playerTurn != testValue){
			testPassed = 1;
		}
		// Change the test value to the next person
		if(testValue == 0){
			 testValue += 1;
		} else {
			testValue -= 1;
		}
		//mmove to the next person's turn
		endTurn(&initGame);
	}
	if(testPassed == 0){
		printf("---PASSED---2 players whose turn works\n");
	} else {
		printf("---FAILED--- players failed\n");
		allTestsPass = 1;
	}

	

	/*  everything to test with 3 players */
	testPassed = 0;
	playerTurn = 0;
	testValue = 0;
	// the game with 3 players
	memset(&initGame, 23, sizeof(struct gameState)); 
	initializeGame(3, kingdom, seed, &initGame);
	for(i = 0; i < 100; i++){
		playerTurn = whoseTurn(&initGame);
		if(playerTurn != testValue){
			testPassed = 1;
		}

		if(testValue < 2){
			testValue += 1;
		} else {
			testValue = 0;
		}
		endTurn(&initGame);
	}
	if(testPassed == 0){
		printf("---PASSED--- 3 players whose turn works\n");
	} else {
		printf("---FAILED--- 3 players failed\n");
		allTestsPass = 1;
	}


	/*  everything to test with 4 players */
	testPassed = 0;
	playerTurn = 0;
	testValue = 0;
	// the game with 3 players
	memset(&initGame, 23, sizeof(struct gameState)); 
	initializeGame(4, kingdom, seed, &initGame);
	for(i = 0; i < 100; i++){
		playerTurn = whoseTurn(&initGame);
		if(playerTurn != testValue){
			testPassed = 1;
		}

		if(testValue < 3){
			testValue += 1;
		} else {
			testValue = 0;
		}
		endTurn(&initGame);
	}
	// let the user know if they test passed with 4 players
	if(testPassed == 0){
		printf("---PASSED--- 4 players whose turn works\n");
	} else {
		printf("---FAILED--- 4 players failed\n");
		allTestsPass = 1;
	}


	if(allTestsPass == 0){
		printf("---PASSED--- all tests passed for whoseTurn()\n");
	} else {
		printf("---FAILED--- there is a problem with the whoseTurn() function\n");
	}
	return 0;
}