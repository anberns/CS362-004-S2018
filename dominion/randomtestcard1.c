/* Aaron Berns
 * randomtestcard1.c tests playAdventurer function
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

void Adventurer(struct gameState *state, int currentPlayer) {

  int drawntreasure = 0; //bug
  int cardDrawn;
  int z = 0;
  int temphand[MAX_HAND];
  
    while(drawntreasure<2){
        printf("drawntreasure: %d, cardDrawn: %d, z: %d\n",  drawntreasure, cardDrawn, z);

        if (state->deckCount[currentPlayer] <1){//if the deck is empty we need to shuffle discard and add to deck
          shuffle(currentPlayer, state);
        }

        drawCard(currentPlayer, state);
        cardDrawn = state->hand[currentPlayer][state->handCount[currentPlayer]-1];//top card of hand is most recently drawn card.
        if (cardDrawn == copper || cardDrawn == silver || cardDrawn == gold) {
          drawntreasure++;
        }
        else{
          temphand[z]=cardDrawn;
          state->handCount[currentPlayer]--; //this should just remove the top card (the most recently drawn one).
          z++;
        }
      }

      while(z-1>=0){
	    state->discard[currentPlayer][state->discardCount[currentPlayer]++]=temphand[z-1]; // discard all cards in play that have been drawn
	    z=z-1;
      }
        printf("\n");
}

void checkAdventurer(int p, struct gameState *post) {
    struct gameState pre;

    memcpy (&pre, post, sizeof(struct gameState));

    Adventurer(post, p);


    // last two cards in hand should be treasure cards
    assert (post->hand[p][post->handCount[p]-1] == copper || post->hand[p][post->handCount[p]-1] == silver || post->hand[p][post->handCount[p]-1] == gold);
    assert (post->hand[p][post->handCount[p]-2] == copper || post->hand[p][post->handCount[p]-2] == silver || post->hand[p][post->handCount[p]-2] == gold);

    // deck = change in discard pile - 2 treasure cards
    printf("postDeck: %d, preDeck: %d, postDis: %d, preDis: %d\n", post->deckCount[p], pre.deckCount[p], post->discardCount[p], pre.discardCount[p]);
    assert (post->deckCount[p] == pre.deckCount[p] - (post->discardCount[p] - pre.discardCount[p]) - 2);


/*
  if (pre.deckCount[p] > 0) {
    pre.handCount[p]++;
    pre.hand[p][pre.handCount[p]-1] = pre.deck[p][pre.deckCount[p]-1];
    pre.deckCount[p]--;
  } else if (pre.discardCount[p] > 0) {
    memcpy(pre.deck[p], post->deck[p], sizeof(int) * pre.discardCount[p]);
    memcpy(pre.discard[p], post->discard[p], sizeof(int)*pre.discardCount[p]);
    pre.hand[p][post->handCount[p]-1] = post->hand[p][post->handCount[p]-1];
    pre.handCount[p]++;
    pre.deckCount[p] = pre.discardCount[p]-1;
    pre.discardCount[p] = 0;
  }

  assert (r == 0);

  assert(memcmp(&pre, post, sizeof(struct gameState)) == 0);
  */
}

int main () {

  int i, n, r, p, deckCount, discardCount, handCount;

  int k[10] = {adventurer, council_room, feast, gardens, mine,
	       remodel, smithy, village, baron, great_hall};

  struct gameState G;

  printf ("Testing playAdventurer.\n");

  printf ("RANDOM TESTS.\n");

  srand(time(NULL));
  //SelectStream(2);
  //PutSeed(3);

  for (n = 0; n < 20000; n++) {
    for (i = 0; i < sizeof(struct gameState); i++) {
      ((char*)&G)[i] = ((rand() % (256 + 1 - 0) + 0));
    }
    p = ((rand() % (3 + 1 - 0) + 0));
    G.deckCount[p] = ((rand() % (MAX_DECK + 1 - 11) + 11));
    G.discardCount[p] = ((rand() % (100 + 1 - 11) + 11));
    G.handCount[p] = ((rand() % (MAX_HAND - 0) + 0));
    for (i = 0; i < G.handCount[p]; ++i) {
        G.hand[p][i] = ((rand() % (24 + 1 - 0) + 0));
    }
    for (i = 0; i < G.deckCount[p]; ++i) {
        G.deck[p][i] = ((rand() % (24 + 1 - 0) + 0));
    }
    

    // ensure at least 3 treasure cards in deck
    int count = 0;
    int randomIndex;
    while (count < 3) {
        randomIndex = ((rand() % (G.deckCount[p] + 1 - 0) + 0));
        if (G.deck[p][randomIndex] != copper || G.deck[p][randomIndex] != silver || G.deck[p][randomIndex] != gold) {
            G.deck[p][randomIndex] = copper;
            count++;
        }
    }

    checkAdventurer(p, &G);
    printf("END OF TEST %d\n", n);
  }

  printf ("ALL TESTS OK\n");
/*
  exit(0);

  printf ("SIMPLE FIXED TESTS.\n");
  for (p = 0; p < 2; p++) {
    for (deckCount = 0; deckCount < 5; deckCount++) {
      for (discardCount = 0; discardCount < 5; discardCount++) {
	for (handCount = 0; handCount < 5; handCount++) {
	  memset(&G, 23, sizeof(struct gameState)); 
	  r = initializeGame(2, k, 1, &G);
	  G.deckCount[p] = deckCount;
	  memset(G.deck[p], 0, sizeof(int) * deckCount);
	  G.discardCount[p] = discardCount;
	  memset(G.discard[p], 0, sizeof(int) * discardCount);
	  G.handCount[p] = handCount;
	  memset(G.hand[p], 0, sizeof(int) * handCount);
	  checkDrawCard(p, &G);
	}
      }
    }
  }
*/
  return 0;
}
