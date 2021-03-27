// ADD FILE HEADER COMMENT


#include "../inc/DX.h"

// ADD METHOD HEADER COMMENT
int genRandSleep(void)
{
    // rand() % (max_number + 1 - minimum_number) + minimum_number
    int result = 0;
    time_t secondsSinceEpoch = 0;
      
    // Intialize random number generator
    srand((unsigned) time(&secondsSinceEpoch));

    // Get random interval to sleep for between 10 and 30 seconds
    result = rand() % (MAX_SLEEP + 1 - MIN_SLEEP) + MIN_SLEEP;

    // Return random interval
    return result;
}