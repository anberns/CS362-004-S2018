/*
 * cardtest3.c : tests minion card
 *
 
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "Minion"

int main() {
    int passFlagAll = 1;
    int passFlag1 = 1;
    int passFlag2 = 1;
    int passFlag3 = 1;
    int passFlag4 = 1;
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

    //set player deck to desired contents for testing
    G.handCount[thisPlayer] = 1;
    G.hand[thisPlayer][0] = minion;
    
    G.deck[thisPlayer][4] = gold;
    G.deck[thisPlayer][3] = province; 
    G.deck[thisPlayer][2] = duchy;
    G.deck[thisPlayer][1] = silver;
    G.deck[thisPlayer][0] = province;

	printf("----------------- Testing Card: %s ----------------\n", TESTCARD);

	// ----------- TEST 1: Add 1 action, discard 1, choice 1 --------------
	printf("\nTEST 1: Add 1 action, discard 1, choice 1\n");
    
    int numActionsBefore = G.numActions;
    int numCoinsBefore = G.coins;
    choice1 = 1;

    //cardEffect(minion, choice1, choice2, choice3, &G, handpos, &bonus);
    callMinion(&G, thisPlayer, handpos, choice1, choice2);

    // check that state values are updated correctly
    if (G.numActions != numActionsBefore + 1 || G.coins != numCoinsBefore + 2 || G.handCount[thisPlayer] != 0) {
        passFlagAll = 0;
        passFlag1 = 0;
    }
	printf("actions = %d, expected = %d\n", G.numActions, numActionsBefore +1);
	printf("coins = %d, expected = %d\n", G.coins, numCoinsBefore +2);
	printf("handCount = %d, expected = %d\n", G.handCount[thisPlayer], 0);

    if (passFlag1) {
        printf("\nPassed\n");
    }
    else {
        printf("\nFailed\n");
    }

	// ----------- TEST 2: Add 1 action, discard 1, choice 2 --------------
	printf("\nTEST 2: Add 1 action, discard 1, choice 2, other player's hand > 4\n");

    numActionsBefore = G.numActions;
    choice1 = 0;
    choice2 = 1;
    handpos = 4;
    G.handCount[thisPlayer] = 5;
    G.hand[thisPlayer][0] = gold;   
    G.hand[thisPlayer][1] = province;   
    G.hand[thisPlayer][2] = silver;   
    G.hand[thisPlayer][3] = estate;   
    G.hand[thisPlayer][4] = minion;   

    // second player hand
    G.handCount[anotherPlayer] = 5;
    G.hand[anotherPlayer][0] = gold;   
    G.hand[anotherPlayer][1] = province;   
    G.hand[anotherPlayer][2] = silver;   
    G.hand[anotherPlayer][3] = estate;   
    G.hand[anotherPlayer][4] = copper;
    G.deck[anotherPlayer][9] = copper;
    G.deck[anotherPlayer][8] = estate; 
    G.deck[anotherPlayer][7] = smithy;
    G.deck[anotherPlayer][6] = adventurer;
    G.deck[anotherPlayer][5] = province;

    //cardEffect(minion, choice1, choice2, choice3, &G, handpos, &bonus);
    callMinion(&G, thisPlayer, handpos, choice1, choice2);
    
    // check that state values are updated correctly
    if (G.numActions != numActionsBefore + 1 || G.handCount[thisPlayer] != 4) {
        passFlagAll = 0;
        passFlag2 = 0;
    }

    // check that cards in hand are correct
    if (G.hand[thisPlayer][0] != gold || G.hand[thisPlayer][1] != province || G.hand[thisPlayer][2] != duchy || G.hand[thisPlayer][3] != silver) {
        passFlagAll = 0;
        passFlag2 = 0;
    }

    if (G.hand[anotherPlayer][0] != copper || G.hand[anotherPlayer][1] != estate || G.hand[anotherPlayer][2] != smithy || G.hand[anotherPlayer][3] != adventurer) {
        passFlagAll = 0;
        passFlag2 = 0;
    }


	printf("actions = %d, expected = %d\n", G.numActions, numActionsBefore +1);
	printf("handCount = %d, expected = %d\n", G.handCount[thisPlayer], 4);   
	printf("player1 card 0 = %d, expected = %d\n", G.hand[thisPlayer][0], gold);   
	printf("player1 card 1 = %d, expected = %d\n", G.hand[thisPlayer][1], province);   
	printf("player1 card 2 = %d, expected = %d\n", G.hand[thisPlayer][2], duchy);   
	printf("player1 card 3 = %d, expected = %d\n", G.hand[thisPlayer][3], silver);   
	printf("player2 card 0 = %d, expected = %d\n", G.hand[anotherPlayer][0], copper);   
	printf("player2 card 1 = %d, expected = %d\n", G.hand[anotherPlayer][1], estate);   
	printf("player2 card 2 = %d, expected = %d\n", G.hand[anotherPlayer][2], smithy);   
	printf("player2 card 3 = %d, expected = %d\n", G.hand[anotherPlayer][3], adventurer);   

    if (passFlag2) {
        printf("\nPassed\n");
    }
    else {
        printf("\nFailed\n");
    }
	// ----------- TEST 3: Add 1 action, discard 1, choice 2, other player's
    // hand = 4 --------------
	printf("\nTEST 3: Add 1 action, discard 1, choice 2, other player's hand = 4\n");

    numActionsBefore = G.numActions;
    choice1 = 0;
    choice2 = 1;
    handpos = 4;
    G.deckCount[thisPlayer] = 5;
    G.handCount[thisPlayer] = 5;
    G.hand[thisPlayer][0] = gold;   
    G.hand[thisPlayer][1] = province;   
    G.hand[thisPlayer][2] = silver;   
    G.hand[thisPlayer][3] = estate;   
    G.hand[thisPlayer][4] = minion;   
    G.deck[thisPlayer][4] = gold;
    G.deck[thisPlayer][3] = province; 
    G.deck[thisPlayer][2] = duchy;
    G.deck[thisPlayer][1] = silver;
    G.deck[thisPlayer][0] = province;

    // second player hand
    G.handCount[anotherPlayer] = 4;
    G.hand[anotherPlayer][0] = gold;   
    G.hand[anotherPlayer][1] = province;   
    G.hand[anotherPlayer][2] = silver;   
    G.hand[anotherPlayer][3] = estate;   

    //cardEffect(minion, choice1, choice2, choice3, &G, handpos, &bonus);
    callMinion(&G, thisPlayer, handpos, choice1, choice2);
    
    // check that state values are updated correctly
    if (G.numActions != numActionsBefore + 1 || G.handCount[thisPlayer] != 4) {
        passFlagAll = 0;
        passFlag3 = 0;
    }

    // check that cards in hand are correct
    if (G.hand[thisPlayer][0] != gold || G.hand[thisPlayer][1] != province || G.hand[thisPlayer][2] != duchy || G.hand[thisPlayer][3] != silver) {
        passFlagAll = 0;
        passFlag3 = 0;
    }

    if (G.hand[anotherPlayer][0] != gold || G.hand[anotherPlayer][1] != province || G.hand[anotherPlayer][2] != silver || G.hand[anotherPlayer][3] != estate) {
        passFlagAll = 0;
        passFlag3 = 0;
    }

	printf("actions = %d, expected = %d\n", G.numActions, numActionsBefore +1);
	printf("handCount = %d, expected = %d\n", G.handCount[thisPlayer], 4);   
	printf("player1 card 0 = %d, expected = %d\n", G.hand[thisPlayer][0], gold);   
	printf("player1 card 1 = %d, expected = %d\n", G.hand[thisPlayer][1], province);   
	printf("player1 card 2 = %d, expected = %d\n", G.hand[thisPlayer][2], duchy);   
	printf("player1 card 3 = %d, expected = %d\n", G.hand[thisPlayer][3], silver);   
	printf("player2 card 0 = %d, expected = %d\n", G.hand[anotherPlayer][0], gold);   
	printf("player2 card 1 = %d, expected = %d\n", G.hand[anotherPlayer][1], province);   
	printf("player2 card 2 = %d, expected = %d\n", G.hand[anotherPlayer][2], silver);   
	printf("player2 card 3 = %d, expected = %d\n", G.hand[anotherPlayer][3], estate);   

    if (passFlag3) {
        printf("\nPassed\n");
    }
    else {
        printf("\nFailed\n");
    }

    // ----------- TEST 4: Add 1 action, discard 1, neither choice --------------
	printf("\nTEST 4: Add 1 action, discard 1, neither choice\n");

    numActionsBefore = G.numActions;
    choice1 = 0;
    choice2 = 0;
    handpos = 4;
    G.deckCount[thisPlayer] = 5;
    G.handCount[thisPlayer] = 5;

    //cardEffect(minion, choice1, choice2, choice3, &G, handpos, &bonus);
    callMinion(&G, thisPlayer, handpos, choice1, choice2);
    
    // check that state values are updated correctly
    if (G.numActions != numActionsBefore + 1 || G.handCount[thisPlayer] != 4) {
        passFlagAll = 0;
        passFlag4 = 0;
    }

	printf("actions = %d, expected = %d\n", G.numActions, numActionsBefore +1);
	printf("handCount = %d, expected = %d\n", G.handCount[thisPlayer], 4);   

    if (passFlag4) {
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


