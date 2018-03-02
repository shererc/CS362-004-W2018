/*****************************************************************
 * Name: Caleb Sherer
 * Due Date: 02/04/2018
 * File Name: unittest1.c
 * Description: Unit test for the "gameOver()" function
 *****************************************************************/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

/* get some colors to make it look like a real test */
	


int main() {
	struct gameState initGame;
	int players = 2;
	//seed doesn't really matter, we just need a working game state to see if the game is over
	int seed = 850;
	int kingdom[10] = {adventurer, smithy, cutpurse, estate, ambassador, outpost, salvager, treasure_map, mine, remodel};
	int gameOver = -100;
	int allTestsPass = 0;

	printf("*************************************************************************\n");
	printf("***********************Testing gameOver() Function***********************\n");
	printf("*************************************************************************\n");

	/* Testing when the game should NOT end */
	//initilize the gamestate
	initializeGame(players, kingdom, seed, &initGame);
	// Check to see if the game has ended
	gameOver = isGameOver(&initGame);
	// First check is right after the game started, and therefore should not be over
	printf("Testing case [normal] causing the game to continue playing: \n");
	// Inform the user the test results
	if(gameOver == 0){
		printf( "---TEST PASSED---the game is not over. \n\n");
	} else {
		printf( "---TEST FAILED--- the game terminated\n\n");
		allTestsPass = 1;
	}


	// Reset the game state
	memset(&initGame, 23, sizeof(struct gameState)); 
	initializeGame(players, kingdom, seed, &initGame);
	// Check to see if we have only one supply pile depleted if the game continues
	printf("Testing case [one supply pile is depleted] causing the game to continue playing: \n");
	// "Deplete" one pile
	initGame.supplyCount[4] = 0;
	// Test the game over function and report results
	gameOver = isGameOver(&initGame);
	if(gameOver == 0){
		printf( "---TEST PASSED--- the game is not over. \n\n");
	} else {
		printf( "---TEST FAILED--- the game terminated\n\n");
		allTestsPass = 1;
	}


	// Reset the game state
	memset(&initGame, 23, sizeof(struct gameState)); 
	initializeGame(players, kingdom, seed, &initGame);
	// Check to see if two supply piles are depleted
	printf("Testing case [two supply piles are depleted] causing the game to continue playing: \n");
	// "Deplete" two supply piles and inform the user of the results
	initGame.supplyCount[6] = 0;
	initGame.supplyCount[8] = 0;
	gameOver = isGameOver(&initGame);
	if(gameOver == 0){
		printf( "---TEST PASSED--- the game is not over. \n\n");
	} else {
		printf( "---TEST FAILED--- the game terminated\n\n");
		allTestsPass = 1;
	}

	/* Now we are testing when the game SHOULD end */
	// Reset the game to try again
	memset(&initGame, 23, sizeof(struct gameState));
	initializeGame(players, kingdom, seed, &initGame); 
	// See if when all province cards are out if the game ends
	printf("Testing case [province deck has been depleted] causing game termination: \n");
	// Deplete the province deck
	initGame.supplyCount[province] = 0;
	// Check to see if the game ends and inform the user
	gameOver = isGameOver(&initGame);
	if(gameOver == 1){
		printf( "---TEST PASSED--- the game ended. \n\n");
	} else {
		printf( "---TEST FAILED--- game did not terminate\n\n");
		allTestsPass = 1;
	}

	// Reset the game state
	memset(&initGame, 23, sizeof(struct gameState)); 
	initializeGame(players, kingdom, seed, &initGame);
	// See if when 3 supply piles are depleted 
	printf("Testing case [three supply piles are depleted] causing game termination: \n");
	initGame.supplyCount[1] = 0;
	initGame.supplyCount[10] = 0;
	initGame.supplyCount[15] = 0;
	// Check for proper behavior and inform the user
	gameOver = isGameOver(&initGame);
	if(gameOver == 1){
		printf( "---TEST PASSED--- the game ended. \n\n");
	} else {
		printf( "---TEST FAILED--- game did not terminate\n\n");
		allTestsPass = 1;
	}


	// Reset the game state
	memset(&initGame, 23, sizeof(struct gameState)); 
	initializeGame(players, kingdom, seed, &initGame);
	// See if when more than 3 supply piles are depleted the game still reacts corectly
	printf("Testing case [four supply piles are depleted] causing game termination: \n");
	initGame.supplyCount[1] = 0;
	initGame.supplyCount[10] = 0;
	initGame.supplyCount[15] = 0;
	initGame.supplyCount[23] = 0;
	// Check for proper behavior and inform the user
	gameOver = isGameOver(&initGame);
	if(gameOver == 1){
		printf( "---TEST PASSED--- the game ended. \n\n");
	} else {
		printf( "---TEST FAILED--- game did not terminate\n\n");
		allTestsPass = 1;
	}

	// Give an overall synopsis of the tests for the user
	if(allTestsPass == 0){
		printf("---ALL TESTS PASSED--- the gameOver() function passes unit testing\n");
	} else {
		printf("---FAILED--- gameOver() function contains a problem, refer to individual test cases above\n");
	}
	return 0;
}