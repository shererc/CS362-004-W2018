/*****************************************************************
 * Name: Caleb Sherer
 * Due Date: 02/04/2018
 * File Name: cardtest4.c
 * Description: Unit test for the Great hall card
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
    int turn = 0;
    int initHandCount = 0;
    int initActionCount = 0;
    int afterHandCount = 0;
    int afterActionCount = 0;
    int initVP = 0;
    int afterVP = 0;
    int i = 0;
    int cardDiscarded = 0;

    printf("*************************************************************************\n");
	printf("***********************Testing GREAT HALL Function***********************\n");
	printf("*************************************************************************\n");

    initializeGame(players, kingdom, seed, &initGame);
    turn = whoseTurn(&initGame);

    //get the initial victory points, hand count, and action count of a user
    initVP = scoreFor(turn, &initGame);
    initHandCount = numHandCards(&initGame);
    initActionCount = initGame.numActions;
    initGame.hand[turn][1] = great_hall;
    afterVP = scoreFor(turn, &initGame);
    cardEffect(great_hall, 0, 0, 0, &initGame, 1, 0);

    //get all of the stats of the user after 
    afterHandCount = numHandCards(&initGame);
    afterActionCount = initGame.numActions;

    for(i = 0; i < numHandCards(&initGame); i++){
        if(initGame.hand[turn][i] == great_hall){
            cardDiscarded = 1;
        }
    }

    // checks to see if the card passes all the test
    if(initHandCount == afterHandCount){
        printf("---PASSED--- a card was played and another card was drawn\n");
    } else {
        printf("---FAILED--- the player's hand contained %d cards instead of %d cards\n\n", afterHandCount, initHandCount);
        allTestsPass = 1;
    }

    if(cardDiscarded == 0){
        printf("---PASSED--- great hall was discarded from the player's hand\n");
    } else {
        printf("---FAILED--- great hall was not discarded from the player's hand\n");
        allTestsPass = 1;
    }

    if(initActionCount + 1 == afterActionCount){
        printf("---PASSED--- the player gained 1 action point from great hall\n");
    } else {
        printf("---FAILED--- the player did not gain a action point from great hall\n");
        allTestsPass = 1;
    }

    if(initVP + 1 == afterVP){
        printf("---PASSED--- the player gained 1 victory point from great hall\n");
    } else {
        printf("---FAILED--- the player did not gain a victory point from great hall\n");
        allTestsPass = 1;
    }

    if(allTestsPass == 0){
        printf("---PASSED--- the great hall card passes all unit tests\n");
    } else {
        printf("---FAILED--- the great hall card has a problem, refer to above unit tests\n");
    }
    return 0;
}