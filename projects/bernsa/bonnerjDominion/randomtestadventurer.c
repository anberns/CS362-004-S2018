/* Aaron Berns
 * randomtestadventurer.c tests playAdventurer function in dominion.c
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

void checkAdventurer(int p, struct gameState *post) {
    struct gameState pre;

    memcpy (&pre, post, sizeof(struct gameState));

    callAdventurer(post, p);


    // last two cards in hand should be treasure cards
    if (!(post->hand[p][post->handCount[p]-1] == copper || post->hand[p][post->handCount[p]-1] == silver || post->hand[p][post->handCount[p]-1] == gold)){
        printf("Last card is treasure FAILED\n");
    }

    if (!(post->hand[p][post->handCount[p]-2] == copper || post->hand[p][post->handCount[p]-2] == silver || post->hand[p][post->handCount[p]-2] == gold)){
        printf("Second to last card is treasure FAILED\n");
    }

    // post deck should equal change in discard pile - 2 treasure cards
    if (!(post->deckCount[p] == pre.deckCount[p] - (post->discardCount[p] - pre.discardCount[p]) - 2)){
        printf("Overall deck changes FAILED\n");
    }
}

int main () {

  int i, n, p;

  struct gameState G;

  printf ("Testing playAdventurer.\n");

  printf ("RANDOM TESTS.\n");

  srand(time(NULL));

  // covers everything except deckCount = 0
  for (n = 0; n < 20000; n++) {
    for (i = 0; i < sizeof(struct gameState); i++) {
      ((char*)&G)[i] = ((rand() % (256 + 1 - 0) + 0));
    }
    p = ((rand() % (3 + 1 - 0) + 0)); // 1-4 players
    G.deckCount[p] = ((rand() % (MAX_DECK + 1 - 10) + 10)); // have to start with at least 10
    G.discardCount[p] = 0;//((rand() % (MAX_DECK + 1 - 0) + 0));
    G.handCount[p] = ((rand() % (MAX_HAND - 5) + 5)); // have to start with at least 5

    // ensure at least 2 treasure cards in deck
    int count = 0;
    int randomIndex;
    while (count < 2) {
        randomIndex = ((rand() % (G.deckCount[p] - 0) + 0));
        if (G.deck[p][randomIndex] != copper && G.deck[p][randomIndex] != silver && G.deck[p][randomIndex] != gold) {
            G.deck[p][randomIndex] = copper;
            count++;
        }
    }

    checkAdventurer(p, &G);
  }

    // ensure that deckCount = 0 condition covered 
    for (n = 0; n < 1000; ++n) {
        for (i = 0; i < sizeof(struct gameState); i++) {
          ((char*)&G)[i] = ((rand() % (256 + 1 - 0) + 0));
        }
        p = ((rand() % (3 + 1 - 0) + 0)); // 1-4 players
        G.deckCount[p] = 0;//((rand() % (MAX_DECK + 1 - 10) + 10)); // have to start with at least 10
        G.discardCount[p] = ((rand() % (MAX_DECK + 1 - 10) + 10));
        G.handCount[p] = ((rand() % (MAX_HAND - 5) + 5)); // have to start with at least 5

        // ensure at least 2 treasure cards in deck
        int count = 0;
        int randomIndex;
        while (count < 2) {
            randomIndex = ((rand() % (G.discardCount[p] - 0) + 0));
            if (G.discard[p][randomIndex] != copper && G.discard[p][randomIndex] != silver && G.discard[p][randomIndex] != gold) {
                G.discard[p][randomIndex] = copper;
                count++;
            }
        }

        checkAdventurer(p, &G);
    }

  printf ("ALL TESTS FINISHED\n");

  return 0;
}
