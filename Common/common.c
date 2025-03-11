#include "common.h"


int generateRandomNumber(int min, int max) {
    // Ensure the random number generator is seeded only once
    static int seeded = 0;
    if (!seeded) {
        srand(time(NULL));  // Seed the random number generator with the current time
        seeded = 1;
    }

    // Generate a random number between min and max inclusive
    return rand() % (max - min + 1) + min;
}
