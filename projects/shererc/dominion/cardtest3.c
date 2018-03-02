/*****************************************************************
 * Name: Caleb Sherer
 * Due Date: 02/04/2018
 * File Name: cardtest3.c
 * Description: Unit test for the "feast" card
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
    int playerDeckCount = 0;
    int afterDeckCount = 0;
    int wasDiscarded = 0;
    int wasGained = 0;
    int j, i;

    printf("********************************************************************\n");
	printf("***********************Testing feast Function***********************\n");
	printf("********************************************************************\n");

    initializeGame(players, kingdom, seed, &initGame);
    turn = whoseTurn(&initGame);
    playerDeckCount = initGame.handCount[turn] + initGame.deckCount[turn] + initGame.discardCount[turn];

    //put feast in the players hand
    initGame.hand[turn][1] = feast;
    cardEffect(feast, cutpurse, 0, 0, &initGame, 1, 0);
    //play the feast card
    afterDeckCount = initGame.handCount[turn] + initGame.deckCount[turn] + initGame.discardCount[turn];
    //check if a card was discarded and gained
    if(playerDeckCount != afterDeckCount){
        printf("---FAILED--- the deck count return %d instead of %d\n", afterDeckCount, playerDeckCount);
        allTestsPass = 1;
    } else {
        printf("---PASSED--- a card was gained and a card was discarded\n");
    }
    
    //  checks if the tets passed and informed the users
    for(j= 0; j < initGame.handCount[turn]; j++){
        if(initGame.hand[turn][j] == feast){
            printf("---FAILED--- feast was not discarded from the player's hand\n");
            allTestsPass = 1;
            wasDiscarded = 1;
        }
    }
    if(wasDiscarded == 0){
        printf("---PASSED--- feast was discarded from the hand\n");
    }

    for(i = 0; i < initGame.discardCount[turn]; i++){
        if(initGame.discard[turn][i] == cutpurse){
            printf("---PASSED--- cutpurse was added to the hand\n");
            wasGained = 1;
        }
    }
    if(wasGained == 0){
        printf("---FAILED--- cutpurse was NOT added to the players hand\n");
        allTestsPass = 1;
    }

    if(allTestsPass == 1){
        printf("---FAILED--- there is a problem with the feast card\n");
    } else {
        printf("---PASSED--- feast passed all unit tests\n");
    }

    return 0;
}