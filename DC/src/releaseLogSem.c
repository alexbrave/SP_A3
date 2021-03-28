/*
 *  FILE          : releaseLogSem.c
 *  PROJECT       : SENG2030-21W-Sec1-System Programming - Assignment #3
 *  PROGRAMMER    : Andrey Takhtamirov, Alex Braverman
 *  FIRST VERSION : March 27, 2020 
 *  DESCRIPTION   : 
 *			This file contains a function that will attempt to release the log
 *          file semaphore, that this process acquired using getOrCreateLogSem()
 *	
*/

#include "../inc/DC.h"

/*
* FUNCTION 		: releaseLogSem
* DESCRIPTION 	: Releases the log file semaphore currently held by this process
* PARAMETERS 	: void : this function takes no parameters
* RETURNS 		: int : returns whether the operation succeeded or failed
*/
int releaseLogSem(void)
{
    // Here we define our acquire and release semaphore operation structs
    struct sembuf acquire_operation = { 0, -1, SEM_UNDO };
    struct sembuf release_operation = { 0, 1, SEM_UNDO };

    // We want to get a key using ftok for our semaphore to be public for all processes
    // that want to use it
    key_t semaphoreKey = 0;

    // We'll use the semaphore key that we got to then get the semaphore ID
    int semaphoreID = 0;

    // We use this counter while trying to get the semaphore
    int getSemAttmptCntr = 0;

    semaphoreKey = ftok(CURRENT_DIRECTORY, SEM_FTOK_ID);

    // Check if the semaphore already exists, hopefully it does
    semaphoreID = semget(semaphoreKey, NUM_OF_SEMS, CHECK_SEM_EXISTS);

    // Attempt to release the semaphore
    if (semop (semaphoreID, &release_operation, 1) == OPERATION_FAILED) 
    {
        // If releasing the semaphore is unsucessful, there is a problem
        return OPERATION_FAILED;
    }
    else
    {
        return OPERATION_SUCCESS;
    }

}