/* unittest4.c : tests supplyCount) */

#include "dominion.h"
#include <stdio.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTFN "supplyCount()"

int main (int argc, char** argv) {

    int passFlag = 1;
    int i;
	struct gameState G;
    
	printf("----------------- Testing Function: %s ----------------\n", TESTFN);

	// ----------- TEST 1: Returns correct count --------------
	printf("TEST 1: Returns correct count\n");
    
    // load card counts
    for (i = 0; i < 25; ++i) {
        G.supplyCount[i] = i*5;
        if (supplyCount(i, &G) != i*5) {
            passFlag = 0;
            printf("failed on card %d\n", i);
            break;
        }
    }
    if (passFlag) {
        printf("passed\n");
    }

    // ----------- TEST 2: Catches negative and large positive card values --------------
	printf("TEST 2: Catches negative and large positive card values\n");
    
    // load negative value and extreme postive
    G.supplyCount[0] = -1;
    G.supplyCount[24] = 100000000;
    if (supplyCount(0, &G) == -1) {
        passFlag = 0;
        printf("failed negative value\n");
    } else {
        printf("passed\n");
    }

    if (supplyCount(24, &G) == 100000000) {
        passFlag = 0;
        printf("failed large positive value\n");
    } else {
        printf("passed\n");
    }

    if (passFlag) {
        printf("SUCCESS: all tests passed\n");
    }

    return 0;
}
