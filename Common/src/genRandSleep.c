/*
 *  FILE          : genRandSleep.c 
 *  PROJECT       : SENG2030-21W-Sec1-System Programming - Assignment #3
 *  PROGRAMMER    : Andrey Takhtamirov, Alex Braverman
 *  FIRST VERSION : March 27, 2020 
 *  DESCRIPTION   : 
 *			This file contains a function that will generate a random period of time
 *          to sleep for between 10 and 30 seconds.
 *	
*/


#include "../inc/genRandSleep.h"

/*
* FUNCTION 		: genRandSleep
* DESCRIPTION 	: Generates a random number between 10 and 30
* PARAMETERS 	: void : this function takes no parameters
* RETURNS 		: int : returns the interval to sleep for
*/
int genRandSleep(void)
{
    int result = 0;
    time_t secondsSinceEpoch = 0;
      
    // Intialize random number generator
    srand((unsigned) time(&secondsSinceEpoch));

    // Get random interval to sleep for between 10 and 30 seconds
    result = rand() % (MAX_SLEEP + 1 - MIN_SLEEP) + MIN_SLEEP;

    // Return random interval
    return result;
}