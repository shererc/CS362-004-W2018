/*****************************************************************
 * Name: Caleb Sherer
 * Due Date: 02/04/2018
 * File Name: cardtest2.c
 * Description: Unit test for the adventurer card
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
    int treasureCount = 0;
    int afterTreasureCount = 0;
    int playerHandCount = 0;
    int afterPlayedHand = 0;
    int adventurerDiscarded = 0;
    int turn = 0;
    int cumuTest = 0;

    printf("*************************************************************************\n");
	printf("***********************Testing Adventurer Function***********************\n");
	printf("*************************************************************************\n");

    //initilize the gamestate
	initializeGame(players, kingdom, seed, &initGame);
    int i, j;
    for(i = 0; i < 2; i++){
        //Get the players turn
        turn = whoseTurn(&initGame);
        //swap the starting hand with 1 adventurer card, this way we know the player only had 1 adventurer card
        initGame.hand[turn][1] = adventurer;
        //get the initial had count
        playerHandCount = numHandCards(&initGame);

        for(j= 0; j < playerHandCount; j++){
            if(initGame.hand[turn][j] == copper || initGame.hand[turn][j] == silver || initGame.hand[turn][j] == gold){
                treasureCount += 1;
            }
        }

        cardEffect(adventurer, 0, 0, 0, &initGame, 1, 0);
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

        // Inform the user about the test results
        printf("TESTING PLAYER %d\n", turn);
        if(afterTreasureCount != treasureCount + 2){
            printf("---FAILED--- treasure count for player %d was %d instead of %d\n", turn, afterTreasureCount, treasureCount + 2);
            allTestsPass = 1;
            cumuTest = 1;
        } else {
             printf("---PASSED--- 2 treasure cards were correctly gained by player %d\n", turn);
        }    
        if((playerHandCount + 1 != afterPlayedHand) || adventurerDiscarded == 1){
            printf("---FAILED--- adventurer was not discarded, count for player %d was %d instead of %d\n", turn, afterPlayedHand, playerHandCount + 1);
            allTestsPass = 1;
            cumuTest = 1;
        } else {
            printf("---PASSED--- adventurer card was successfully discarded %d\n", turn);
        }
        if(allTestsPass == 1){
            printf("---FAILED--- unit tests for player %d failed\n\n", turn);
        }else {
            printf("---PASSED--- all tests for player %d passed the unit test\n\n", turn);
        }
        endTurn(&initGame);
        afterTreasureCount = 0;
        treasureCount = 0;
        
    }

        if(cumuTest == 1){
            printf("---FAILED--- the adventurer card has problems, refer to above unit tests\n");
        }else {
            printf("---PASSED--- the adventurer card has passed all unit tests\n");
        }

        return 0;

}