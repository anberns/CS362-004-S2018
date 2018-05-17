/* Aaron Berns
 * randomtestcard2.c tests callSteward function
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>
#include "rngs.h"

#define DEBUG 0
#define NOISY_TEST 1

void checkSteward(int p, struct gameState *post, int handPos, int choice1, int choice2, int choice3) {
    struct gameState pre;

    memcpy (&pre, post, sizeof(struct gameState));

    callSteward(post, p, handPos, choice1, choice2, choice3);

    // if choice1 = 1, deck should have two less cards
    if (choice1 == 1) {
        if (!(post->deckCount[p] == pre.deckCount[p] - 2)){
            printf("Choice1 = 1: Deck loses 2 cards FAILED\n");
        }
    }

    // choice1 = 2, coins increase by two
    else if (choice1 == 2) {
        if (!(post->coins == pre.coins + 2)){
            printf("Choice1 = 2: 2 coins added FAILED\n");
        }
    }

    // three cards discarded from hand
    else {
        if (!(post->handCount[p] == pre.handCount[p] - 3)){
            printf("Choice1 = 3: 3 cards discarded FAILED\n");
        }
 
    }

    // only Steward is kept, other two trashed if choice1 != 1 or 2
    if (!(post->playedCardCount == pre.playedCardCount + 1)){
        printf("Steward kept, if others, trashed FAILED\n");
    }
 
    int i, countpre = 0; 
    int countpost = 0;
    for (i = 0; i < post->handCount[p]; ++i) {
        if (post->hand[p][i] == steward) {
            countpost++;
        }
    }

    // possibility that another steward card is discarded
    if (choice1 == 3 && choice2 == steward) {
        countpost++;
    }
    if (choice1 == 3 && choice3 == steward) {
        countpost++;
    }

    for (i = 0; i < pre.handCount[p]; ++i) {
        if (pre.hand[p][i] == steward) {
            countpre++;
        }
    }
    
    // can be triggered by bug in discardCard() which can change index of steward
    // card before it is discarded
    if (!(countpost == countpre - 1)){
        printf("Steward kept part 2 FAILED\n");
    }
}

int main () {

  int i, n, p, choice1, choice2, choice3, possible;

  struct gameState G;

  printf ("Testing callSteward().\n");

  printf ("RANDOM TESTS.\n");

  srand(time(NULL));

  for (n = 0; n < 20000; n++) {
    for (i = 0; i < sizeof(struct gameState); i++) {
      ((char*)&G)[i] = ((rand() % (256 + 1 - 0) + 0));
    }
    p = ((rand() % (3 + 1 - 0) + 0)); // 1-4 players
    G.deckCount[p] = ((rand() % (MAX_DECK + 1 - 2) + 2)); // have to start with at least 2 
    G.discardCount[p] = ((rand() % (MAX_DECK + 1 - 0) + 0));
    G.playedCardCount = ((rand() % (MAX_DECK - 0) + 0)); // must be real index for discardCard function
    G.handCount[p] = ((rand() % (MAX_HAND - 3) + 3)); // have to start with at least 3 so that discard 2 option works
    
    // choice1 needs to be limited so that all options get roughly equal coverage
    choice1 = ((rand() % (3 + 1 - 1) + 1));

    // ensure steward card is in deck, handPos will be this randomly generated
    // index
    int randomIndex;
    randomIndex = ((rand() % (G.handCount[p] - 0) + 0));
    if (G.hand[p][randomIndex] != steward) {
        G.hand[p][randomIndex] = steward;
    }

    // choices 2 and 3 need to be actual indexes of hand and different cards and
    // not steward card being played
    do {
        possible = ((rand() % (G.handCount[p] - 0) + 0));
    } while (possible == randomIndex); 

    choice2 = possible;

    do {
        possible = ((rand() % (G.handCount[p] - 0) + 0));
    } while (possible == randomIndex || possible == choice2);
    choice3 = possible;


    checkSteward(p, &G, randomIndex, choice1, choice2, choice3);
  }

  printf ("ALL TESTS FINISHED\n");

  return 0;
}
