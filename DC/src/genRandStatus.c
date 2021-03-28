/*
 *  FILE          : genRandStatus.c
 *  PROJECT       : SENG2030-21W-Sec1-System Programming - Assignment #3
 *  PROGRAMMER    : Andrey Takhtamirov, Alex Braverman
 *  FIRST VERSION : March 27, 2020 
 *  DESCRIPTION   : 
 *			This file contains a function that will generate a random status for
 *          the data creator to send to the data reader.
 *	
*/

#include "../inc/DC.h"

/*
* FUNCTION 		: genRandStatus
* DESCRIPTION 	: Generates a random status between 0 and 6
* PARAMETERS 	: void : this function takes no parameters
* RETURNS 		: int : returns the random status
*/
int genRandStatus(void)
{
    int result = 0;
    time_t secondsSinceEpoch = 0;
      
    // Intialize random number generator
    srand((unsigned) time(&secondsSinceEpoch));

    // Get random status
    result = rand() % NUM_OF_STATUSES;

    // Return random status
    return result;
}