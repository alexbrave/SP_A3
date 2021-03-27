/*
 *  FILE          : dc.c
 *  PROJECT       : SENG2030-21W-Sec1-System Programming - Assignment #3
 *  PROGRAMMER    : Andrey Takhtamirov, Alex Braverman
 *  FIRST VERSION : March 24, 2020 
 *  DESCRIPTION   : 
 *			This file contains the entry point, main() for the Data Creator program.
 *          The purpose of this program is to create generate messages and send them 
 *          on a message queue to be received/read by another program, the Dat Reader.
 *	
*/

#include "../inc/DX.h"

int main(void)
{

    //////////////////
    // Set-up Logic //
    //////////////////
    

    // The PID of the data corruptor
    pid_t dxPID = 0;

    // This is a pointer to the shared memory master list
    MasterList* masterList = NULL;

    // Key for the DR's shared memory
    key_t sharedMemKey = 0;

    // Message queue ID that will be obtained from DR's shared memory
    int msgQueID = 0;

    // ID of the shared memory that the DX will use
    int sharedMemID = OPERATION_FAILED;

    // Variable indicating if DX should shutdown after sending status
    bool shutdownDX = false;

    // Interval for which the DX should sleep for
    bool randSleepInterval = 0;

    // Counter for max number of retries to attach to shared memory
    int retryCounter = MAX_ATTACH_RETRIES;

    // Store the result of our attempt to execute a WOD action
    int wODActResult = 0;

    // The data corruptor has been started and it's first step is to get its PID
    dxPID = getpid();

    // Next the data corruptor will get the key, via which it will determine if the message queue exists
    sharedMemKey = ftok(AGREED_UPON_PATH, AGREED_UPON_VALUE);

    if(sharedMemKey == OPERATION_FAILED)
    {
        // ADD LOGIC LATER TO HANDLE IF KEY CREATION FAILED AND REMOVE PRINT STATEMENT
        printf("\nCreating the shared memory key failed.\n");
        // RELEASE SEMAPHORE AFTER LOGGING
        return 0;
    }

    // Use key to check if shared memory exists on a loop
    sharedMemID = shmget(sharedMemKey, SHARED_MEM_SIZE, CHECK_SHR_MEM_EXIST);
    // ADD LOGIC FOR IF THIS FAILS

    masterList = (MasterList*)shmat(sharedMemID, NULL, SHM_RDONLY);
    retryCounter--;

    // While the data corruptor is not able to attach to the shared memory, it will keep trying,
    // up to 100 times, and sleep for 10 seconds in between attempts
    while((int)masterList == OPERATION_FAILED && retryCounter > 0)
    {
        sleep(CANT_ATTACH_SLEEP);
        retryCounter--;
    }

    if(retryCounter == 0)
    {
        // LOG THAT ATTACHING TO MEMORY FAILED SO SHUTTING DOWN, AND QUIT
    }


    // Attempt to send meaningless message to check if message queue exists
    if(checkQueExists(masterList->msgQueueID) == OPERATION_FAILED)
    {
        // LOG AND EXIT
        printf("Could not send message, possibly because message queue is gone!");
        return 0;
    }

    ///////////////
    // Main Loop //
    ///////////////
    // If DX got out of the loop, that means it was able to attach to the shared memory and is ready
    // to cause havoc!

    while(true)
    {
        // Generate random number of seconds to sleep for between 10 and 30
        randSleepInterval = genRandSleep();
        sleep(randSleepInterval);

        // Here we call the function that will execute a random WOD action
        wODActResult = executeWODAct(masterList);

        // If we were able to delete the message queue, or the message queue was already gone,
        // or if we failed to execute the random WOD action, set the flag indicating if we should
        // quit to true
        if(wODActResult == MSG_Q_DEL_SHUT_D ||
           wODActResult == MSG_Q_NOT_THERE  ||
           wODActResult == ACT_FAILED_QUIT)
        {
            shutdownDX = true;
        }


        if(shutdownDX == true)
        {
            // LOG AND EXIT
            return 0;
        }
        else
        {
            // Generate a random sleep interval, and sleep for that many seconds
            randSleepInterval = genRandSleep();
            sleep(randSleepInterval);
        }
    }
    
}








