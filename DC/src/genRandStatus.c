// ADD FILE HEADER COMMENT


#include "../inc/DC.h"

// ADD METHOD HEADER COMMENT
int genRandStatus(void)
{
    // const int statusMin = EVERYTHING_OK_INT;
    // const int statusMax = MACH_OFFLINE_INT;

    int result = 0;
    time_t secondsSinceEpoch = 0;
      
    // Intialize random number generator
    srand((unsigned) time(&secondsSinceEpoch));

    // Get random status
    result = rand() % NUM_OF_STATUSES;

    // Return random status
    return result;
}