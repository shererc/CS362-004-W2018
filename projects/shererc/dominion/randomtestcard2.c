/*****************************************************************
 * Name: Caleb Sherer
 * Due Date: 02/18/2018
 * File Name: randomtestcard2.c
 * Description: random test for the feast card
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
    int turn = 0;
    int playerDeckCount = 0;
    int afterDeckCount = 0;
    int wasGained = 0;
    int j, i;
    int randomCard;
    int cardGained = 0;
    int discardedFeast = 0;
    int cardAquired= 0;
    int cardCost;
    int testNumber = 0;
    int tooMuch;

    printf("********************************************************************\n");
	printf("***********************Testing Feast Function***********************\n");
	printf("********************************************************************\n");

    //play the feast card 1000 times.
    while(testNumber < 1000){
        wasGained = 0;
        cardCost = 10;
        initializeGame(players, kingdom, seed, &initGame);
        turn = whoseTurn(&initGame);
        playerDeckCount = initGame.handCount[turn] + initGame.deckCount[turn] + initGame.discardCount[turn];

        //put feast in the players hand
        initGame.hand[turn][0] = feast;
        while(cardCost > 5){
            randomCard = rand() % 10;
            cardCost = kingdom[randomCard];
        }
        //play the card and take a random kingdom card
        cardEffect(feast, kingdom[randomCard], 0, 0, &initGame, 1, 0);
        //play the feast card
        afterDeckCount = initGame.handCount[turn] + initGame.deckCount[turn] + initGame.discardCount[turn];
        //check if a card was discarded and gained
        
        if(playerDeckCount + 1 != afterDeckCount){
            cardGained++;
        }
        
        //  checks if the tets passed and informed the users
        for(j= 0; j < initGame.handCount[turn]; j++){
            if(initGame.hand[turn][j] == feast){
                discardedFeast++;
                allTestsPass = 1;
            }
        }
        // checks to ensure that there is the correct numbe rof cards in hand
        for(i = 0; i < initGame.handCount[turn]; i++){
            if(initGame.hand[turn][i] == kingdom[randomCard]){
                wasGained = 1;
                if(getCost(kingdom[randomCard]) > 5){
                    tooMuch++;
                }
            }
        }
        if(wasGained == 0){
            cardAquired++;
            allTestsPass = 1;
        }
        testNumber++;
    }

    //There was a card gained greater than 5 cost that is the limit for feast
    if(tooMuch > 0){
        printf("---FAILED--- the card that was gained had a cost greater than 5 %d times out of 1000\n", tooMuch);
    } else {
        printf("---PASSED--- all cards that were gained had a cost equal to or less than 5\n");
    }
    // The new kingdom card was not placed into the player's hand
    if(cardGained > 0){
        printf("---FAILED--- a new card was not gained when playing feast %d times out of 1000\n", cardGained);
    } else {
        printf("---PASSED--- a new card was successfully gained each time feast was played \n");
    }

    //feast was not discarded
    if(discardedFeast > 0){
        printf("---FAILED--- feast was not discarded %d times out of 1000\n", discardedFeast);
    } else {
        printf("---PASSED--- feast was discarded each time it was played\n");
    }
    //There was a card taht was gained, but the requested one was not the one gained
    if(cardAquired > 0){
        printf("---FAILED--- The card requested was not gained, but another card was %d times out of 1000\n", cardAquired);
    } else {
        printf("---PASSED--- The card requested was gained each time feast was played\n");
    }
    //Lets the user know if all tests have passed
    if(allTestsPass == 1){
        printf("---FAILED--- there is a problem with the feast card\n");
    } else {
        printf("---PASSED--- feast passed all unit tests\n");
    }

    return 0;
}