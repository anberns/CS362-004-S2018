/*
 * cardtest1.c : tests adventurer card
 *
 
 */


#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "adventurer"
/*
void callAdventurer(struct gameState *state, int currentPlayer) {
  int drawntreasure=0; //bug, remove init
  int cardDrawn;
  int z = 0;
  int temphand[MAX_HAND];

    while(drawntreasure<2){
        if (state->deckCount[currentPlayer] <1){//if the deck is empty we need to shuffle discard and add to deck
          shuffle(currentPlayer, state);
        }
        drawCard(currentPlayer, state);
        cardDrawn = state->hand[currentPlayer][state->handCount[currentPlayer]-1];//top card of hand is most recently drawn card.
        if (cardDrawn == copper || cardDrawn == silver || cardDrawn == gold)
          drawntreasure++;
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
}
*/

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
    G.handCount[thisPlayer] = 0;

    G.deck[thisPlayer][4] = gold;
    G.deck[thisPlayer][3] = province; 
    G.deck[thisPlayer][2] = duchy;
    G.deck[thisPlayer][1] = silver;
    G.deck[thisPlayer][0] = province;

	printf("----------------- Testing Card: %s ----------------\n", TESTCARD);

	// ----------- TEST 1: Treasure cards in hand, others discarded --------------
	printf("TEST 1: Treasure kept, others discarded\n");
    
    //cardEffect(adventurer, choice1, choice2, choice3, &G, handpos, &bonus);
    callAdventurer(&G, thisPlayer);
    
    // check hand, should have copper and silver
    if (G.hand[thisPlayer][0] != gold || G.hand[thisPlayer][1] != silver) {
        passFlag = 0;
    }
	printf("hand card = %d, expected = %d\n", G.hand[thisPlayer][0], gold);
    printf("hand card = %d, expected = %d\n", G.hand[thisPlayer][1], silver);

    // check discard, should have estate and duchy
    if (G.discard[thisPlayer][0] != duchy || G.discard[thisPlayer][1] != province) {
        passFlag = 0;
    }
	printf("discard card = %d, expected = %d\n", G.discard[thisPlayer][0], duchy);
    printf("discard card = %d, expected = %d\n", G.discard[thisPlayer][1], province);
	// ----------- TEST 2: choice1 = 2 = +2 coins --------------
	//printf("TEST 2: choice1 = 2 = +2 coins\n");

    if (passFlag) {
	    printf("\n >>>>> SUCCESS: Testing complete %s <<<<<\n\n", TESTCARD);
    }


	return 0;
}


