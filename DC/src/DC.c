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

#include "../inc/DC.h"

int main(void)
{

    //////////////////
    // Set-up Logic //
    //////////////////


    // The PID of the data creator
    pid_t dcPID = 0;

    // The key for the message queue
    key_t msgQueKey = 0;

    // Message queue ID
    int msgQueID = 0;

    // Random status
    int randStatus = 0;

    // Variable indicating if DC should shutdown after sending status
    bool shutdownDC = false;

    // Interval for which the DC should sleep for
    int sleepInterval = 0;

    // The data creator has been started and it's first step is to get its PID
    dcPID = getpid();


    // Next the data creator will get the key, via which it will determine if the message queue exists
    msgQueKey = ftok(CURRENT_DIRECTORY, AGREED_UPON_VALUE);

    if(msgQueKey == OPERATION_FAILED)
    {
        // ADD LOGIC LATER TO HANDLE IF KEY CREATION FAILED AND REMOVE PRINT STATEMENT
        printf("\nCreating the key failed.\n");
        // RELEASE SEMAPHORE AFTER LOGGING
        return 0;
    }

    // Use key to check if message queue exists on a loop
    msgQueID = msgget(msgQueKey, CHECK_MSG_Q_EXISTS);


    // While the data creator is not able to get the message queue, it will keep trying to get it,
    // and sleep for 10 seconds in between attempts
    while(msgQueID == OPERATION_FAILED)
    {
        sleep(MSG_Q_NOT_EXIST_SLEEP);
        msgQueID = msgget(msgQueKey, CHECK_MSG_Q_EXISTS);
    }


    ///////////////
    // Main Loop //
    ///////////////
    // If DC got out of the loop, that means it got the message queue and should now try to send a message

    while(true)
    {
        // Generate random status to send to DR
        randStatus = genRandStatus();

        // If the status is that machine is offline, then this indicates that we must close the DC
        if(randStatus == MACH_OFFLINE_INT)
        {
            shutdownDC = true;
        }

        // Attempt to send message
        if(sendMessage(dcPID, msgQueID, randStatus) == OPERATION_FAILED)
        {
            // log and exit
            printf("Could not send message, possibly because message queue is gone!");
            logMessage(dcPID, SHUTDOWN_INT, MSG_QUE_GONE_MSG);
            // RELEASE SEMAPHORE
            return 0;
        }

        if(shutdownDC == true)
        {
            // log and exit
            printf("Sent status 6, Machine Off-Line, shutting down.");
            logMessage(dcPID, SHUTDOWN_INT, MACH_OFF_SHUTD_MSG);
            // RELEASE SEMAPHORE
            return 0;
        }
        else
        {
            // Generate a random sleep interval, and sleep for that many seconds
            sleepInterval = genRandSleep();
            sleep(sleepInterval);
        }
    }
    
}








