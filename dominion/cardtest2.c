/*
 * cardtest2.c : tests smithy card
 *
 
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "Smithy"

int main() {
    int passFlag = 1;
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
	struct gameState G, testG;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};


	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);

    //set player deck to desired contents for testing
    G.handCount[thisPlayer] = 1;
    G.hand[thisPlayer][0] = smithy;
    
    G.deck[thisPlayer][4] = gold;
    G.deck[thisPlayer][3] = province; 
    G.deck[thisPlayer][2] = duchy;
    G.deck[thisPlayer][1] = silver;
    G.deck[thisPlayer][0] = province;

	printf("----------------- Testing Card: %s ----------------\n", TESTCARD);

	// ----------- TEST 1: Three cards added --------------
	printf("TEST 1: Three cards added\n");
    
    //cardEffect(smithy, choice1, choice2, choice3, &G, handpos, &bonus);
    callSmithy(&G, thisPlayer, 0);

    // check hand, should have gold, province, duchy
    if (G.hand[thisPlayer][0] != duchy || G.hand[thisPlayer][1] != gold || G.hand[thisPlayer][2] != province) {
        passFlag = 0;
    }
	printf("hand count = %d, expected = %d\n", G.handCount[thisPlayer], 3);
	printf("hand card = %d, expected = %d\n", G.hand[thisPlayer][0], duchy);
    printf("hand card = %d, expected = %d\n", G.hand[thisPlayer][1], gold);
    printf("hand card = %d, expected = %d\n", G.hand[thisPlayer][2], province);

   	/* ----------- TEST 2: Shuffle, treasure cards in hand, others discarded --------------
	printf("TEST 2: Shuffle, treasure kept, others discarded\n");

    // initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);
    G.handCount[thisPlayer] = 0;

    //set player deck to desired contents for testing
    G.deckCount[thisPlayer] = 0;

    //cardEffect(adventurer, choice1, choice2, choice3, &G, handpos, &bonus);
    callAdventurer(&G, thisPlayer);
    
    // check hand, should have copper and silver
    
    if (G.hand[thisPlayer][0] != copper || G.hand[thisPlayer][1] != copper) {
        passFlag = 0;
    }
	printf("hand card = %d, expected = %d\n", G.hand[thisPlayer][0], copper);
    printf("hand card = %d, expected = %d\n", G.hand[thisPlayer][1], copper);

    // check discard, should have estate and duchy
    for (i = 0; i < G.discardCount[thisPlayer]; ++i) {
        if (G.discard[thisPlayer][0] != estate) {
            passFlag = 0;
        }
    }
    */

    if (passFlag) {
	    printf("\n >>>>> SUCCESS: Testing complete %s <<<<<\n\n", TESTCARD);
    }


	return 0;
}


