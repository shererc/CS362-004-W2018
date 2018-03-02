/*****************************************************************
 * Name: Caleb Sherer
 * Due Date: 02/18/2018
 * File Name: randomtestcard1.c
 * Description: Random test for the smithy card
 *****************************************************************/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
#include <time.h>
#include <stdlib.h>

int main(){
    srand(time(NULL));
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
	printf("*********************************************************************\n");
	printf("***********************Testing Smithy Function***********************\n");
	printf("*********************************************************************\n");
    // Initilize the variables
    int i, k;
    int afterInDiscard = 0;
    int initInDiscard = 0;
    int smithyCounter = 0;
    int numberSmithy = 0;
    int smithyPosition = 0;
    int incorrectDraw = 0;
    int smithyPlayed = 0;
    int badDiscard = 0;


    //Now we will go until smithy has been played 1000 times
    while(smithyCounter < 1000){
        //init new game with new cards for randomness
        initializeGame(players, kingdom, seed, &initGame);
         for(i = 0; i < 2; i++){
        //Get the players turn
        turn = whoseTurn(&initGame);
        initGame.deckCount[i] = rand() % MAX_DECK; //Pick random deck size out of MAX DECK size
        initGame.discardCount[i] = rand() % MAX_DECK;
        initGame.handCount[i] = 5;
        //Place a random number of smithy cards in each players hand
        numberSmithy = rand() % 5;
        //give each player 3 smithy cards to start the game
        initGame.hand[turn][numberSmithy] = smithy;
    }
        smithyPosition = -1;
        smithyPlayed = 0;
        initInDiscard = 0;
        afterInDiscard = 0;
        //Get the player whose turn it is and their hand count
        turn = whoseTurn(&initGame);
        playerHandCount = numHandCards(&initGame);
        //Get the total number of smithy's in the discard pile to compare to after

        initInDiscard = initGame.discardCount[turn];
        //See if the player has a smithy card in their hand
        for(k = 0; k < playerHandCount; k++){
            if(initGame.hand[turn][k] == smithy){
                smithyPosition = k;
                break;
            }
        }
        //If a smithy card was found, play it
        if(smithyPosition != -1){
            if(initGame.hand[turn][smithyPosition] == smithy){
            cardEffect(initGame.hand[turn][smithyPosition], 0, 0, 0, &initGame, smithyPosition, 0);
            if(initGame.hand[turn][smithyPosition] == smithy){
                smithyDiscarded++;
            }
            smithyPlayed = 1;
            //increment the total number of smithy's played
            smithyCounter++;
            }
        }
        //If a smithy card was played run tests
        if(smithyPlayed == 1){
            //check to see that the correct number of cards were drawn
            afterSmithyCount = numHandCards(&initGame);
            if(playerHandCount + 2 != afterSmithyCount){
                //if they wern't increment the count
                incorrectDraw++;
            }
            afterInDiscard = initGame.discardCount[turn];
                //If the smithy was not discarded, increment the counter
            if(initInDiscard + 1 != afterInDiscard){
                badDiscard++;
            }
        }
        //Go to the next players turn
        endTurn(&initGame);
    }
    //now warn the user if the card wasn't discarded
    if(smithyDiscarded > 0){
        printf("---FAILED--- the smithy card was not discarded properly %d times out of 1000\n", smithyDiscarded);
        allTestsPass = 1;
    } else {
        printf("---PASSED--- the smithy card was discarded properly\n");
    }
    //report any errors in card numbers to the user
    if(incorrectDraw > 0){
        printf("---FAILED--- The smithy card did not draw the correct number of cards %d times out of 1000\n", incorrectDraw);
        allTestsPass = 1;
    } else {
        printf("---PASSED--- the smithy card drew the correct number of cards \n");
    }
    // Report if the smithy card was not put into the discard pile
    if(badDiscard > 0){
        printf("---FAILED--- The smithy card was not placed in the discard pile after being played %d times out of 1000\n", badDiscard);
        allTestsPass = 1;
    } else {
        printf("---PASSED--- the smithy card was discarded after it was played \n");
    }
    //report if all tests pasts
    if(allTestsPass == 1){
		printf("---ERROR--- Smithy effect has a problem\n");
	} else {
		printf("---ALL PASSED--- Smithy card effect passed the unit test\n");
	}

    return 0;
}