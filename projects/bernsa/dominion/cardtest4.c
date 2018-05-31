/*
 * cardtest4.c : tests steward card
 *
 
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "Steward"

int main() {
    int passFlagAll = 1;
    int passFlag1 = 1;
    int passFlag2 = 1;
    int passFlag3 = 1;
    int newCards = 0;
    int discarded = 1;
    int xtraCoins = 0;
    int shuffledCards = 0;

    int i, j, m;
    int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
    int remove1, remove2;
    int seed = 1000;
    int numPlayers = 2;
    int thisPlayer = 0;
    int anotherPlayer = 1;
	struct gameState G, testG;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};


	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);

	printf("\n----------------- Testing Card: %s ----------------\n", TESTCARD);

	// ----------- TEST 1: Add 2 cards to hand --------------
	printf("\nTEST 1: Add 2 cards to hand\n");
    
    //set player deck to desired contents for testing
    choice1 = 1;
    choice2 = 0;
    choice3 = 0;
    handpos = 0;
    G.handCount[thisPlayer] = 2;
    G.hand[thisPlayer][0] = steward;   
    G.hand[thisPlayer][1] = province;   
    //G.hand[thisPlayer][2] = silver;   
    //G.hand[thisPlayer][3] = estate;   
    //G.hand[thisPlayer][4] = minion;       
    G.deckCount[thisPlayer] = 5;
    G.deck[thisPlayer][4] = estate;
    G.deck[thisPlayer][3] = duchy; 
    G.deck[thisPlayer][2] = duchy;
    G.deck[thisPlayer][1] = silver;
    G.deck[thisPlayer][0] = province;

    cardEffect(steward, choice1, choice2, choice3, &G, handpos, &bonus);

    // check that state values are updated correctly
    if (G.handCount[thisPlayer] != 3) {
        passFlagAll = 0;
        passFlag1 = 0;
    }

    // check that cards in hand are correct
    if (G.hand[thisPlayer][0] != duchy || G.hand[thisPlayer][1] != province || G.hand[thisPlayer][2] != estate) {
        passFlagAll = 0;
        passFlag1 = 0;
    }

	printf("handCount = %d, expected = %d\n", G.handCount[thisPlayer], 3);   
	printf("player1 card 0 = %d, expected = %d\n", G.hand[thisPlayer][0], duchy);   
	printf("player1 card 1 = %d, expected = %d\n", G.hand[thisPlayer][1], province);   
	printf("player1 card 2 = %d, expected = %d\n", G.hand[thisPlayer][2], estate);   

    if (passFlag1) {
        printf("\nPassed\n");
    }
    else {
        printf("\nFailed\n");
    }	
    
    // ----------- TEST 2: Add 2 coins --------------
	printf("\nTEST 2: Add 2 coins\n");

    int numCoinsBefore = G.coins;
    choice1 = 2;
    choice2 = 0;
    choice3 = 0;
    handpos = 1;
    G.handCount[thisPlayer] = 5;
    G.hand[thisPlayer][0] = gold;   
    G.hand[thisPlayer][1] = steward;   
    G.hand[thisPlayer][2] = silver;   
    G.hand[thisPlayer][3] = estate;   
    G.hand[thisPlayer][4] = minion;   

    cardEffect(steward, choice1, choice2, choice3, &G, handpos, &bonus);

    // check that state values are updated correctly
    if (G.coins != numCoinsBefore +2 || G.handCount[thisPlayer] != 4) {
        passFlagAll = 0;
        passFlag2 = 0;
    }

    // check that cards in hand are correct
    if (G.hand[thisPlayer][0] != gold || G.hand[thisPlayer][1] != minion || G.hand[thisPlayer][2] != silver || G.hand[thisPlayer][3] != estate) {
        passFlagAll = 0;
        passFlag2 = 0;
    }

	printf("handCount = %d, expected = %d\n", G.handCount[thisPlayer], 4);   
	printf("coins = %d, expected = %d\n", G.coins, numCoinsBefore +2);   
	printf("player1 card 0 = %d, expected = %d\n", G.hand[thisPlayer][0], gold);   
	printf("player1 card 1 = %d, expected = %d\n", G.hand[thisPlayer][1], minion);   
	printf("player1 card 2 = %d, expected = %d\n", G.hand[thisPlayer][2], silver);   
	printf("player1 card 3 = %d, expected = %d\n", G.hand[thisPlayer][3], estate); 

    if (passFlag2) {
        printf("\nPassed\n");
    }
    else {
        printf("\nFailed\n");
    }	
 
    
	// ----------- TEST 3: Discard 2 from hand --------------
	printf("\nTEST 3: Discard 2 from hand\n");

    choice1 = 0;
    choice2 = 1;
    choice3 = 3;
    handpos = 4;
    G.handCount[thisPlayer] = 5;
    G.hand[thisPlayer][4] = steward;   
    
    cardEffect(steward, choice1, choice2, choice3, &G, handpos, &bonus);

    // check that state values are updated correctly
    if (G.handCount[thisPlayer] != 2) {
        passFlagAll = 0;
        passFlag3 = 0;
    }

    // check that cards in hand are correct
    if (G.hand[thisPlayer][0] != gold || G.hand[thisPlayer][1] != silver) {
        passFlagAll = 0;
        passFlag3 = 0;
    }

	printf("handCount = %d, expected = %d\n", G.handCount[thisPlayer], 2);   
	printf("player1 card 0 = %d, expected = %d\n", G.hand[thisPlayer][0], gold);   
	printf("player1 card 1 = %d, expected = %d\n", G.hand[thisPlayer][1], silver);   

    if (passFlag3) {
        printf("\nPassed\n");
    }
    else {
        printf("\nFailed\n");
    }	
 
    if (passFlagAll) {
	    printf("\n >>>>> SUCCESS: Testing complete %s <<<<<\n\n", TESTCARD);
    }


	return 0;
}


