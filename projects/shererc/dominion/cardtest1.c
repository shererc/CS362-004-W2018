/*****************************************************************
 * Name: Caleb Sherer
 * Due Date: 02/04/2018
 * File Name: cardtest1.c
 * Description: Unit test for the smithy card
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
    int playerHandCount = 0;
    int afterSmithyCount = 0;
    int smithyDiscarded = 0;
    int turn = 0;
    int correctCardNumber = 0;

	printf("*********************************************************************\n");
	printf("***********************Testing Smithy Function***********************\n");
	printf("*********************************************************************\n");

	//initilize the gamestate
	initializeGame(players, kingdom, seed, &initGame);
    int i, j;
    //have both players play a smithy card
    for(i = 0; i < 2; i++){
        //Get the players turn
        turn = whoseTurn(&initGame);
        //swap the starting hand with 1 smithy card, this way we know the player only had 1 smithy card
        initGame.hand[turn][1] = smithy;
        //get the initial had count
        playerHandCount = numHandCards(&initGame);
        //play the smithy card
        cardEffect(smithy, 0, 0, 0, &initGame, 1, 0);
        //get the hand count after smithy is played
        afterSmithyCount = numHandCards(&initGame);

        //loop through the player's hand and make sure the smithy card was discarded
        for(j = 0; j < afterSmithyCount; j++){
            if(initGame.hand[turn][j] == smithy){
                //throw flags if it wasn't
                smithyDiscarded = 1;
                allTestsPass = 1;
            }
        }
        //now warn the user if the card wasn't discarded
        if(smithyDiscarded == 1){
            printf("---FAILED--- player %d did not discard smithy after it was played\n", turn);
        } else {
            printf("---PASSED--- player %d discarded the smithy card after played\n", turn);
        }
        //The correct card number should be the playerHandCount +2 this is because
        // smithy will draw 3 cards, but then the smithy card is discarded, so it is
        // a net gain of 2 cards
        correctCardNumber = playerHandCount + 2;
        //report any errors in card numbers to the user
        if((correctCardNumber) != afterSmithyCount){
            printf("---FAILED--- player %d hand count is %d instead of %d\n", turn, afterSmithyCount, correctCardNumber);
            allTestsPass = 1;
        } else {
            printf("---PASSED--- player handcount %i is correct after smithy\n", turn);
        }
        endTurn(&initGame);
    }

    //report if all tests pasts
    if(allTestsPass == 1){
		printf("---ERROR--- Smithy effect has a problem\n");
	} else {
		printf("---ALL PASSED--- Smithy card effect passed the unit test\n");
	}

    return 0;
}