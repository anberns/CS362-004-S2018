/* Aaron Berns
 * randomtestcard1.c tests callSmithy function
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

void checkSmithy(int p, struct gameState *post, int handPos) {
    struct gameState pre;

    memcpy (&pre, post, sizeof(struct gameState));

    smithyCard(p, post, handPos);

    // deck should have three less cards
    if (!(post->deckCount[p] == pre.deckCount[p] - 3)){
        printf("Deck loses 3 cards FAILED\n");
    }

    // hand should have two more cards (draw 3 - discard smithy)
    if (!(post->handCount[p] == pre.handCount[p] + 2)){
        printf("Hand gains 2 cards FAILED\n");
    }

    // Smithy card should have been discarded
    if (!(post->hand[p][handPos] != smithy)){
        printf("Smithy discarded FAILED\n");
    }
}

int main () {

  int i, n, p;

  struct gameState G;

  printf ("Testing callSmithy().\n");

  printf ("RANDOM TESTS.\n");

  srand(time(NULL));

  for (n = 0; n < 20000; n++) {
    for (i = 0; i < sizeof(struct gameState); i++) {
      ((char*)&G)[i] = ((rand() % (256 + 1 - 0) + 0));
    }
    p = ((rand() % (3 + 1 - 0) + 0)); // 1-4 players
    G.deckCount[p] = ((rand() % (MAX_DECK + 1 - 10) + 10)); // have to start with at least 10
    G.discardCount[p] = ((rand() % (MAX_DECK + 1 - 0) + 0));
    G.playedCardCount = ((rand() % (MAX_DECK + 1 - 0) + 0)); // must be real index for discardCard function
    G.handCount[p] = ((rand() % (MAX_HAND + 1 - 1) + 1)); // have to start with at least 1

    // ensure smithy card is in deck, handPos will be this randomly generated
    // index
    int randomIndex;
    randomIndex = ((rand() % (G.handCount[p] - 0) + 0));
    if (G.hand[p][randomIndex] != smithy) {
        G.hand[p][randomIndex] = smithy;
    }

    checkSmithy(p, &G, randomIndex);
  }

  printf ("ALL TESTS FINISHED\n");

  return 0;
}
