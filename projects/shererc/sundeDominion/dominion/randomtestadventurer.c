/*****************************************************************
 * Name: Caleb Sherer
 * Due Date: 02/18/2018
 * File Name: randomtestadventurer.c
 * Description: Random test for the adventurer card
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
 struct gameState initGame;
	int players = 2;
	//seed doesn't really matter, we just need a working game state to see if the game is over
	int seed = 850;
	int kingdom[10] = {adventurer, smithy, cutpurse, estate, ambassador, outpost, salvager, treasure_map, mine, remodel};
	int allTestsPass = 0;
    int treasureCount = 0;
    int afterTreasureCount = 0;
    int playerHandCount = 0;
    int afterPlayedHand = 0;
    int adventurerDiscarded = 0;
    int turn = 0;
    int numberAdventurer;
    int adventurerCount = 0;
    int treasureTest = 0;
    int discardTest = 0;

    printf("*************************************************************************\n");
	printf("***********************Testing Adventurer Function***********************\n");
	printf("*************************************************************************\n");

    //initilize the gamestate
    int j;
    while(adventurerCount < 1000){
    initializeGame(players, kingdom, seed, &initGame);
        //Get the players turn
        turn = whoseTurn(&initGame);
        initGame.deckCount[0] = rand() % MAX_DECK; //Pick random deck size out of MAX DECK size
        initGame.discardCount[0] = rand() % MAX_DECK;
        initGame.handCount[0] = 5;
        //swap the starting hand with 1 adventurer card, this way we know the player only had 1 adventurer card
        numberAdventurer = rand() % 5;
        initGame.hand[turn][numberAdventurer] = adventurer;
        //get the initial had count
        playerHandCount = numHandCards(&initGame);

        for(j= 0; j < playerHandCount; j++){
            if(initGame.hand[turn][j] == copper || initGame.hand[turn][j] == silver || initGame.hand[turn][j] == gold){
                treasureCount += 1;
            }
        }

        cardEffect(adventurer, 0, 0, 0, &initGame, numberAdventurer, 0);
        afterPlayedHand = numHandCards(&initGame);

        for(j= 0; j < afterPlayedHand; j++){
            if(initGame.hand[turn][j] == copper || initGame.hand[turn][j] == silver || initGame.hand[turn][j] == gold){
                afterTreasureCount += 1;
            }
        }

        for(j = 0; j < afterPlayedHand; j++){
            if(initGame.hand[turn][j] == adventurer){
                //throw flags if it wasn't
                adventurerDiscarded = 1;
                allTestsPass = 1;
            }
        }
        //checks to ensure that there are 2 more treasure cards in the hand than previously
        if(afterTreasureCount != treasureCount + 2){
            treasureTest++;
            allTestsPass = 1;
        }  
        //checks to make sure that the adventurer was discarded
        if((playerHandCount + 1 != afterPlayedHand) || adventurerDiscarded == 1){
            discardTest++;
            allTestsPass = 1;
        }
        afterTreasureCount = 0;
        treasureCount = 0;
        adventurerCount++;
    }

    //tells the user if the treasure card was not gained
    if(treasureTest > 0){
        printf("---FAILED--- the correct number of treasure cards were not gained %d times out of 1000\n", treasureTest);
    } else {
        printf("---PASSED--- the correct number of treasure cards were gained when adventurer was played\n");
    }

    //tells if the adventurer card was not discarded
    if(discardTest > 0 ){
        printf("---FAILED--- the adventurer card was not discarded %d times out of 1000\n", discardTest);
    } else {
        printf("---PASSED--- the adventurer card was discarded corectly each time\n");
    }
    //Tells if the card passed all unit testing
    if(allTestsPass == 1){
        printf("---FAILED--- the adventurer card has problems, refer to above unit tests\n");
    }else {
        printf("---PASSED--- the adventurer card has passed all unit tests\n");
    }

    return 0;

}