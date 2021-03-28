/*
 *  FILE          : DR.c
 *  PROJECT       : SENG2030-21W-Sec1-System Programming - Assignment #3
 *  PROGRAMMER    : Andrey Takhtamirov, Alex Braverman
 *  FIRST VERSION : March 26, 2020 
 *  DESCRIPTION   : 
 *			This file contains the entry point, main() for the Data Reader program.
 *          The purpose of this program is to read messages from a queue and populate 
 *          a struct, MasterList.
 *	
*/
#include "../inc/DR.h"

int main(void)
{
    key_t msgKey;
    bool done = false;

    int recMsg = 0;
    int queueID = 0;

    int sharedMemKey = 0;
    int sharedMemID = 0;
    int i = 0;

    MasterList *list = NULL;
    MESSAGE msg;

    // create key for message queue
    msgKey = ftok(CURRENT_DIRECTORY, AGREED_UPON_VALUE);
    if (msgKey == NOT_FOUND)
    {
        logError("Message queue key could not be created.");
        fflush(stdout);
        return ERROR;
    }

    // check if message queue already exists, if not, make a new queue
    queueID = msgget(msgKey, CHECK_MSG_QUEUE_EXISTS);

    if (queueID == NOT_FOUND)
    {
        queueID = msgget(msgKey, IPC_CREAT | CREATE_VALUE);

        if (queueID == NOT_FOUND)
        {
            logError("Error creating message queue.");
            return ERROR;
        }
    }

    // get key for shared memory
    sharedMemKey = ftok(CURRENT_DIRECTORY, SHARED_MEMORY_KEY);
    if (sharedMemKey == NOT_FOUND)
    {
        logError("Cannot create key for new shared memory.");
        return ERROR;
    }

    sharedMemID = shmget(sharedMemKey, sizeof(MasterList), 0);

    // check for existing shared memory
    if (sharedMemID == NOT_FOUND)
    {
        sharedMemID = shmget(sharedMemKey, sizeof(MasterList), IPC_CREAT | CREATE_VALUE);
        if (sharedMemID == NOT_FOUND)
        {
            logError("Cannot allocate new shared memory.");
            return ERROR;
        }
    }

    // attach shared memory
    list = (MasterList *)shmat(sharedMemID, NULL, 0);
    if (list == NULL)
    {
        logError("Cannot attach to shared memory.");
        return ERROR;
    }

    // init data to zeros
    for (i = 0; i < MAX_DC_ROLES; i++)
    {
        list->dc[i].dcProcessID = 0;
        list->dc[i].lastTimeHeardFrom = 0;
    }

    list->numberOfDCs = 0;
    list->msgQueueID = queueID;

    sleep(SECONDS_TO_SLEEP_ON_STARTUP);
    fflush(stdout); // flush output to fix hang on sleep bug

    // listen for messages
    while (!done)
    {
        if (receiveMessage(list, &msg) == NOT_FOUND)
        {
            logError("Error reading message queue. Check that it exists.");
            break;
        }

        // check for inactive machines (more than 35 seconds has passed with no message)
        // check for offline status
        if (checkInactiveClients(list) == NOT_FOUND || checkStatus(list, msg) == NOT_FOUND)
        {
            break;
        }

        // sleep for 1.5 seconds.
        sleep(SECONDS_TO_SLEEP_BETWEEN_MESSAGES);
    }

    // clean up resources
    msgctl(queueID, IPC_RMID, (struct msqid_ds *)NULL);

    shmdt(list);

    shmctl(sharedMemID, IPC_RMID, 0);

    return 0;
}
