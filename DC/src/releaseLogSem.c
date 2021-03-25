// ADD FILE HEADER COMMENT


#include "../inc/DC.h"

// ADD METHOD HEADER COMMENT

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

    if (semop (semaphoreID, &release_operation, 1) == OPERATION_FAILED) 
    {
        printf ("(USER1) GRRRRR.... Can't release critical region\n");
        exit (4);
        return OPERATION_FAILED;
    }
    else
    {
        return OPERATION_SUCCESS;
    }

}