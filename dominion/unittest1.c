/* unittest1.c : tests TestfullDeckCount() */

#include "dominion.h"
#include <stdio.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTFN "TestfullDeckCount()"

int TestfullDeckCount(int player, int card, struct gameState *state) {
  int i;
  int count = 0;

  for (i = 0; i < state->deckCount[player]; i++)
    {
      if (state->deck[player][i] == card) count++;
    }

  for (i = 0; i < state->handCount[player]; i++)
    {
      if (state->hand[player][i] == card) count++;
    }

  for (i = 0; i < state->discardCount[player]; i++)
    {
      if (state->discard[player][i] == card) count++;
    }

  return count;
}

int main (int argc, char** argv) {

    const int player1 = 1;
    const int player2 = 2;
    const int player3 = 3;
    const int player4 = 4;

    int passFlag = 1;
    int i;
    int seed = 1000;
    int numPlayers = 2;
    int thisPlayer = 0;
	struct gameState G, testG;
    /*
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};

	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);
    */

	printf("----------------- Testing Function: %s ----------------\n", TESTFN);

	// ----------- TEST 1: All decks contain some of card  --------------
	printf("TEST 1: All three decks contain card \n");

    // load G with test values
    G.deckCount[player1] = 10;
    for (i = 0; i < 5; ++i) {
        G.deck[player1][i] = estate;
    }
    for (i = 5; i < 10; ++i) {
        G.deck[player1][i] = copper;
    }
    G.handCount[player1] = 5;
    for (i = 0; i < 2; ++i) {
        G.hand[player1][i] = copper;
    }
    for (i = 2; i < 5; ++i) {
        G.hand[player1][i] = estate;
    }
    G.discardCount[player1] = 10;
    for (i = 0; i < 5; ++i) {
        G.discard[player1][i] = copper;
    }
    for (i = 5; i < 10; ++i) {
        G.discard[player1][i] = estate;
    }

    int count = TestfullDeckCount(1, estate, &G);
    if (count == 13) {
        printf("passed\n");
    } else {
        printf("failed\n");
        passFlag = 0;
    }

    // ----------- TEST 2: All decks do not contain card  --------------
	printf("TEST 2: All three decks do not contain card \n");

    count = TestfullDeckCount(1, province, &G);
    if (count == 0) {
        printf("passed\n");
    } else {
        printf("failed\n");
        passFlag = 0;
    }

    // ----------- TEST 3: Some decks contain card  --------------
	printf("TEST 3: Some decks contain card \n");

    // load G with test values
    for (i = 5; i < 10; ++i) {
        G.discard[player1][i] = gold;
    }

    count = TestfullDeckCount(1, gold, &G);
    if (count == 5) {
        printf("passed\n");
    } else {
        printf("failed\n");
        passFlag = 0;
    }

    if (passFlag) {
        printf("SUCCESS: all tests passed\n");
    }

  return 0;
}
