// ADD FILE HEADER COMMENT


#include "../inc/DC.h"

// ADD METHOD HEADER COMMENT
int getOrCreateLogSem(void)
{
    // SEE MODULE 6 INCLUDE FILE FOR MORE DETAILS
    struct sembuf acquire_operation = { 0, -1, SEM_UNDO };
    struct sembuf release_operation = { 0, 1, SEM_UNDO };

    // Our semaphore initial value is 1, indicating that only 1 process can use the resource at a time
    unsigned short init_values[NUM_OF_SEMS] = { SEM_INITAL_VALUE };


    // We want to get a key using ftok for our semaphore to be public for all processes
    // that want to use it
    key_t semaphoreKey = 0;

    // We'll use the semaphore key that we got to then get the semaphore ID
    int semaphoreID = 0;

    // Here we'll get the key via which we'll be able to get the semaphore
    semaphoreKey = ftok(CURRENT_DIRECTORY, SEM_FTOK_ID);

    // Check if the semaphore already exists
    semaphoreID = semget(semaphoreKey, NUM_OF_SEMS, CHECK_SEM_EXISTS);
    // ADD LOGIC FOR IF THIS FAILS

    // Create a semaphore if one doesn't already exist
    if(semaphoreID == OPERATION_FAILED)
    {
        semaphoreID = semget(semaphoreKey, NUM_OF_SEMS, (IPC_CREAT | 0660));
        // ADD LOGIC FOR IF THIS FAILS

        // Initialize the semaphore to 1, the value in our init_values
        if (semctl(semaphoreID, 0, SETALL, init_values) == OPERATION_FAILED) 
        {
            // ADD LOGIC FOR IF THIS FAILS
        }
    } 

    // If we made it this far, that means the semaphore exists, 
    // or was created and initialized successfully!
    // Attempt to acquire the semaphore
    
    // We will try to get the semaphore 200 times, if that fails, we'll assume it's gone
    // and return that we were unsuccessfull
    if (semop(semaphoreID, &acquire_operation, NUM_SOP_STRUCTS) == OPERATION_FAILED)
    {
        printf ("(USER1) GRRRRR.... Can't start critical region\n");
    }

    return OPERATION_SUCCESS;

}
