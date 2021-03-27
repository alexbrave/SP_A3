#include "../inc/DR.h"

int receiveMessage(MasterList *list, MESSAGE *msg);
int checkIDinMasterList(MasterList list, int clientID);
void displayMasterList(MasterList *list);
int checkInactiveClients(MasterList *list);
void reorder(MasterList *list);
int removeClient(MasterList *list, int clientIndex);
int checkStatus(MasterList *list, MESSAGE msg);

int main(void)
{
    key_t msgKey;
    bool done = false;

    int recMsg;
    int queueID;

    int sharedMemKey;
    int sharedMemID;

    MasterList *list;
    MESSAGE msg;

    // create key for message queue
    msgKey = ftok(CURRENT_DIRECTORY, AGREED_UPON_VALUE);
    if (msgKey == NOT_FOUND)
    {
        printf("ERROR Key could not be created!\n");
        // need to log
        fflush(stdout);
        return 1;
    }

    // check if message queue already exists, if not, make a new queue
    queueID = msgget(msgKey, CHECK_MSG_QUEUE_EXISTS);

    if (queueID == NOT_FOUND)
    {
        printf("Existing message queue not found\n");
        queueID = msgget(msgKey, IPC_CREAT | 0660);

        if (queueID == NOT_FOUND)
        {
            printf("Error creating message queue!\n");
            // need to log
            return 1;
        }
    }

    // get key for shared memory
    sharedMemKey = ftok(CURRENT_DIRECTORY, SHARED_MEMORY_KEY);
    if (sharedMemKey == NOT_FOUND)
    {
        printf("Cannot allocate key for shared memory\n");
        // log
        return 1;
    }

    sharedMemID = shmget(sharedMemKey, sizeof(MasterList), 0);

    // check for existing shared memory
    if (sharedMemID == NOT_FOUND)
    {
        printf("No Shared-Memory currently available - so create!\n");
        sharedMemID = shmget(sharedMemKey, sizeof(MasterList), IPC_CREAT | 0660);
        if (sharedMemID == NOT_FOUND)
        {
            printf("Cannot allocate new shared memory!\n");
            // log
            return 1;
        }
    }

    /* now allow the PRODUCER (server) to attach to our shared memory and begin
	   producing data to be read ... */

    list = (MasterList *)shmat(sharedMemID, NULL, 0);
    if (list == NULL)
    {
        printf("Cannot attach to shared memory!\n");
        // log
        return 1;
    }

    // init data to zeros
    for (int i = 0; i < MAX_DC_ROLES; i++)
    {
        list->dc[i].dcProcessID = 0;
        list->dc[i].lastTimeHeardFrom = 0;
    }

    list->numberOfDCs = 0;
    list->msgQueueID = queueID;

    printf("Shared-Memory ID is %d\n", sharedMemID);

    printf("Message queue opened: %d\n", list->msgQueueID);

    sleep(SECONDS_TO_SLEEP_ON_STARTUP);

    printf("Listening...\n");
    fflush(stdout); // flush output to fix hang on sleep bug

    // listen for messages
    while (!done)
    {
        if (receiveMessage(list, &msg) == NOT_FOUND)
        {
            printf("something bad happened!\n");
            // need to log
            break;
        }

        // check for inactive machines (more than 35 seconds has passed with no message)
        // check for offline status
        if (checkInactiveClients(list) == NOT_FOUND || checkStatus(list, msg) == NOT_FOUND)
        {
            printf("All DCs have gone offline or terminated - DR TERMINATING\n");
            break;
        }

        displayMasterList(list);

        // sleep for 1.5 seconds.
        sleep(SECONDS_TO_SLEEP_BETWEEN_MESSAGES);
    }

    // clean up resources
    printf("Detaching from Shared-Memory\n");
    shmdt (list);

    printf("Removing the Shared-Memory resource\n");
    shmctl (sharedMemID, IPC_RMID, 0);

    return 0;
}


// receives a message
int receiveMessage(MasterList *list, MESSAGE *msg)
{
    int recMsg;

    // receive a message
    recMsg = msgrcv(list->msgQueueID, (void *)msg, sizeof(MESSAGE), 0, 0);
    if (recMsg == NOT_FOUND)
    {
        return NOT_FOUND;
    }

    printf("Received message: %d, status %d\n", msg->PID, msg->status);

    // check if PID is new
    int clientIndex = checkIDinMasterList(*list, msg->PID);
    time_t seconds = time(NULL);

    if (clientIndex == NOT_FOUND)
    {
        // client is new, add to MasterList
        //printf("adding PID %d to MasterList\n", msg->PID);
        list->dc[list->numberOfDCs].dcProcessID = msg->PID;
        list->dc[list->numberOfDCs].lastTimeHeardFrom = seconds;
        list->numberOfDCs += 1;
    }
    else
    {
        // only update last heard from time
        //printf("client %d already exists, update time\n", msg->PID);
        list->dc[clientIndex].lastTimeHeardFrom = seconds;
    }

    return SUCCESSFUL;
}

// check if ID is in MasterList, returning the index if contained, -1 else
int checkIDinMasterList(MasterList list, int clientID)
{
    int listCounter = 0;

    while (listCounter < list.numberOfDCs)
    {
        if (list.dc[listCounter].dcProcessID == clientID)
        {
            // exists in list, return index
            return listCounter;
        }
        listCounter++;
    }

    return NOT_FOUND;
}

// display master list
void displayMasterList(MasterList *list)
{
    printf("Master List:\n");

    for (int i = 0; i < list->numberOfDCs; i++)
    {
        printf("process: %d\t", list->dc[i].dcProcessID);
        printf("time: %ld\n", list->dc[i].lastTimeHeardFrom);
    }
}


// checks all DCs for inactivity, removing inactive clients.
int checkInactiveClients(MasterList *list)
{
    time_t currentTime = time(NULL);
    int i = 0;

    for (i = 0; i < list->numberOfDCs; i++)
    {
        // if last heard from time is more than 35 seconds less than current time,
        // client is inactive
        if (currentTime - list->dc[i].lastTimeHeardFrom > INACTIVE_CLIENT_TIME_SECONDS)
        {
            return removeClient(list, i);
        }
    }
}


// reorders the MasterList (removing empty elements between DCs)
void reorder(MasterList *list)
{
    for (int i = 0; i < list->numberOfDCs; i++)
    {
        if (list->dc[i].dcProcessID == 0 && list->dc[i].lastTimeHeardFrom == 0)
        {
            // find the next non empty element
            for (int j = i + 1; j < list->numberOfDCs; j++)
            {
                if (list->dc[j].dcProcessID != 0 && list->dc[j].lastTimeHeardFrom != 0)
                {
                    list->dc[i].dcProcessID = list->dc[j].dcProcessID;
                    list->dc[i].lastTimeHeardFrom = list->dc[j].lastTimeHeardFrom;

                    list->dc[j].dcProcessID = 0;
                    list->dc[j].lastTimeHeardFrom = 0;
                    break;
                }
            }
        }
    }
}


// checks the status of an incoming message and removes the DC if OFFLINE
int checkStatus(MasterList *list, MESSAGE msg)
{
    int i = 0;

    if (msg.status == MACHINE_OFFLINE)
    {
        // find and remove offline DC from MasterList
        for (i = 0; i < list->numberOfDCs; i++)
        {
            if (list->dc[i].dcProcessID == msg.PID)
            {
                // this is our offline client
                return removeClient(list, i);
            }
        }
    }
}


// remove client of given index from MasterList
int removeClient(MasterList *list, int clientIndex)
{
    printf("client removed %d\n", list->dc[clientIndex].dcProcessID);

    // remove DC from MasterList struct
    list->dc[clientIndex].dcProcessID = 0;
    list->dc[clientIndex].lastTimeHeardFrom = 0;

    // collpase the MasterList struct (reorder to make all elements adjacent)
    reorder(list);

    // update number of DCs
    list->numberOfDCs -= 1;

    if (list->numberOfDCs == 0)
    {
        return NOT_FOUND;
    }

    return SUCCESSFUL;
}
