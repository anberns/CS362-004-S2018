/* unittest3.c : tests whoseTurn() */

#include "dominion.h"
#include <stdio.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTFN "whoseTurn()"

int main (int argc, char** argv) {

    int passFlag = 1;
    int i;
	struct gameState G;
    
	printf("\n----------------- Testing Function: %s ----------------\n", TESTFN);

	// ----------- TEST 1: Players 1-4 --------------
	printf("TEST 1: Players 1-4\n");
    
    for (i = 1; i <= MAX_PLAYERS; ++i) {
        G.whoseTurn = i;
        if (whoseTurn(&G) != i) {
            passFlag = 0;
            printf("failed\n");
            break;
        }
        printf("passed\n");
    }

    // ----------- TEST 2: Players 0, 5 --------------
	printf("TEST 2: Invalid players 0,5\n");
    
    G.whoseTurn = 0;
    if (whoseTurn(&G) == 0) {
        passFlag = 0;
        printf("failed\n");
    } else {
        printf("passed\n");
    }

    G.whoseTurn = 5;
    if (whoseTurn(&G) == 5) {
        passFlag = 0;
        printf("failed\n");
    } else {
        printf("passed\n");
    }

    if (passFlag) {
        printf("SUCCESS: all tests passed\n");
    }

    return 0;
}
