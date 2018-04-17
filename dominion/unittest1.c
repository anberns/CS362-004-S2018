/* unittest1.c : tests fullDeckCountTest() */

#include "dominion.h"
#include <stdio.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTFN "fullDeckCountTest()"

int fullDeckCountTest(int player, int card, struct gameState *state) {
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

    int passFlag = 1;
    int i;
	struct gameState G;
    
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

    int count = fullDeckCountTest(1, estate, &G);
    if (count == 13) {
        printf("passed\n");
    } else {
        printf("failed\n");
        passFlag = 0;
    }

    // ----------- TEST 2: All decks do not contain card  --------------
	printf("TEST 2: All three decks do not contain card \n");

    count = fullDeckCountTest(1, province, &G);
    if (count == 0) {
        printf("passed\n");
    } else {
        printf("failed\n");
        passFlag = 0;
    }

    // ----------- TEST 3: Lower boundary case ------------
	printf("TEST 3: Lower boundary of all decks 0\n");

    // load G with test values
    G.deckCount[player1] = 0;
    G.handCount[player1] = 0;
    G.discardCount[player1] = 0;

    count = fullDeckCountTest(1, gold, &G);
    if (count == 0) {
        printf("passed\n");
    } else {
        printf("failed\n");
        passFlag = 0;
    }

    // ----------- TEST 4: Upper boundary case ------------
	printf("TEST 4: Upper boundary of all decks MAX_DECK gold\n");

    // load G with test values
    G.deckCount[player1] = MAX_DECK;
    for (i = 0; i < MAX_DECK; ++i) {
        G.deck[player1][i] = gold;
    }

    G.handCount[player1] = MAX_DECK;
    for (i = 0; i < MAX_DECK; ++i) {
        G.hand[player1][i] = gold;
    }

    G.discardCount[player1] = MAX_DECK;
    for (i = 0; i < MAX_DECK; ++i) {
        G.discard[player1][i] = gold;
    }

    count = fullDeckCountTest(1, gold, &G);
    if (count == MAX_DECK * 3) {
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
