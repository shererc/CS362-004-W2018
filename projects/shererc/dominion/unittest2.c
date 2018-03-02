/*****************************************************************
 * Name: Caleb Sherer
 * Due Date: 02/04/2018
 * File Name: unittest2.c 
 * Description: Unit test for the getCost() function
 *****************************************************************/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define LENGTH 28

typedef struct testCards {
	int value;
	int intName;
	int passedTest;
	char strName[100];
} testCards;

int main(){
	
	//Create an array of structs that stores all of the cards, values, and names
	testCards cardsArray[LENGTH] = {
		{0, curse, 0, "curse"},
		{2, estate, 0, "estate"},
		{5, duchy, 0, "duchy"},
		{8, province, 0, "province"},
		{0, copper, 0, "copper"},
		{3, silver, 0, "silver"},
		{6, gold, 0, "gold"},
		{6, adventurer, 0, "adventurer"},
		{5, council_room, 0, "council_room"},
		{4, feast, 0, "feast"},
		{4, gardens, 0, "gardens"},
		{5, mine, 0, "mine"},
		{4, remodel, 0, "remodel"},
		{4, smithy, 0, "smithy"},
		{3, village, 0, "village"},
		{4, baron, 0, "baron"},
		{3, great_hall, 0, "great_hall"},
		{5, minion, 0, "minion"},
		{3, steward, 0, "steward"},
		{5, tribute, 0, "tribute"},
		{3, ambassador, 0, "ambassador"},
		{4, cutpurse, 0, "cutpurse"},
		{2, embargo, 0, "embargo"},
		{5, outpost, 0, "outpost"},
		{4, salvager, 0, "salvager"},
		{4, sea_hag, 0, "sea_hag"},
		{4, treasure_map, 0, "treasure_map"},
		{-1, -1, 0, "badCard"}
	};

	printf("************************************************************************\n");
	printf("***********************Testing getCost() Function***********************\n");
	printf("************************************************************************\n");

	int i = 0;
	int allTestsPast = 0;
	//go through each card
	for(i = 0; i < LENGTH; i++){
		// see if the returned value matches what the card should be
		cardsArray[i].passedTest = getCost(cardsArray[i].intName);
		//inform the user
		if(cardsArray[i].value == cardsArray[i].passedTest){
			printf( "---TEST PASSED--- card %s has a value of %i \n", cardsArray[i].strName, cardsArray[i].value);
		} else {
			printf( "---TEST FAILED--- card %s returned with a value of %i instead of the correct value %i \n", cardsArray[i].strName, cardsArray[i].value, cardsArray[i].passedTest);
			allTestsPast = 1;
		}
	}
	if(allTestsPast == 0){
		printf("---ALL TESTS PASSED--- getCost() works correctly\n");
	} else {
		printf("---FAILED--- getCost() function contains a problem\n");
	}
	return 0;
}