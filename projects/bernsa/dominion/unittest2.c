/* unittest2.c : tests isGameOver() */

#include "dominion.h"
#include <stdio.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTFN "isGameOver()"

int main (int argc, char** argv) {

    int passFlag = 1;
    int i;
	struct gameState G;
    
	printf("\n----------------- Testing Function: %s ----------------\n", TESTFN);

	// ----------- TEST 1: Out of province cards --------------
	printf("TEST 1: Out of province cards\n");

    // set province cards to 0
    G.supplyCount[province] = 0;
    if (isGameOver(&G)) {
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

    if (isGameOver(&G)) {
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
    
    if (isGameOver(&G) != 1) {
        printf("passed no supplies at 0\n");
    } else {
        printf("failed no supplies at 0\n");
        passFlag = 0;
    }
    
    // two supplies at 0 
    G.supplyCount[0] = 0;
    G.supplyCount[24] = 0;

    if (isGameOver(&G) != 1) {
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
