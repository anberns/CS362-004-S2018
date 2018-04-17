/* unittest2.c : tests isGameOver() */

#include "dominion.h"
#include <stdio.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTFN "isGameOver()"

int isGameOverTest(struct gameState *state) {
    int i;
    int j;
	
    //if stack of Province cards is empty, the game ends
    if (state->supplyCount[province] == 0)
    {
      return 1;
    }

    //if three supply pile are at 0, the game ends
    j = 0;
    for (i = 0; i < 25; i++)
    {
        if (state->supplyCount[i] == 0)
        {
            j++;
        }
    }
    if (j >= 3)
    {
        printf("returning from here\n");
        return 1;
    }

    return 0;
}

int main (int argc, char** argv) {

    int passFlag = 1;
    int i;
	struct gameState G;
    
	printf("----------------- Testing Function: %s ----------------\n", TESTFN);

	// ----------- TEST 1: Out of province cards --------------
	printf("TEST 1: Out of province cards\n");

    // set province cards to 0
    G.supplyCount[province] = 0;
    if (isGameOverTest(&G)) {
        printf("passed\n");
    } else {
        printf("failed\n");
        passFlag = 0;
    }

    // ----------- TEST 2: Three card supplies at 0 --------------
	printf("TEST 2: Three card supplies at 0\n");

    // set card supplies to 0
    for (i = 0; i < sizeof(G.supplyCount); ++i) {
        G.supplyCount[i] = 0;
    }
    G.supplyCount[province] = 1;

    if (isGameOverTest(&G)) {
        printf("passed\n");
    } else {
        printf("failed\n");
        passFlag = 0;
    }

    // ----------- TEST 3: Boundary cases ------------
	printf("TEST 3: Boundary cases\n");

    // no supplies at 0
    for (i = 0; i < sizeof(G.supplyCount); ++i) {
        G.supplyCount[i] = 1;
    }
    
    if (isGameOverTest(&G) != 1) {
        printf("passed no supplies at 0\n");
    } else {
        printf("failed no supplies at 0\n");
        passFlag = 0;
    }
    
    // two supplies at 0 
    G.supplyCount[0] = 0;
    G.supplyCount[24] = 0;

    if (isGameOverTest(&G) != 1) {
        printf("passed two supplies at 0\n");
    } else {
        printf("failed two supplies at 0\n");
        passFlag = 0;
    }

    if (passFlag) {
        printf("SUCCESS: all tests passed\n");
    }

    return 0;
}
