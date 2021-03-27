#include "../inc/DR.h"

int checkIDinMasterList(MasterList list, int clientID);
void displayMasterList(MasterList *list);

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
	sharedMemKey = ftok (CURRENT_DIRECTORY, SHARED_MEMORY_KEY);
	if (sharedMemKey == NOT_FOUND) 
	{ 
	  printf ("Cannot allocate key for shared memory\n");
      // log
	  return 1;
	}

    sharedMemID = shmget (sharedMemKey, sizeof (MasterList), 0);

    // check for existing shared memory
	if (sharedMemID == NOT_FOUND) 
	{
		printf ("No Shared-Memory currently available - so create!\n");
		sharedMemID = shmget (sharedMemKey, sizeof (MasterList), IPC_CREAT | 0660);
		if (sharedMemID == NOT_FOUND) 
		{
		  printf ("Cannot allocate new shared memory!\n");
          // log
		  return 1;
		}
	}

    /* now allow the PRODUCER (server) to attach to our shared memory and begin
	   producing data to be read ... */

	list = (MasterList *)shmat (sharedMemID, NULL, 0);
	if (list == NULL) 
	{
	  printf ("Cannot attach to shared memory!\n");
      // log
	  return 3;
	}


	// init data to zeros
	for (int i = 0; i < MAX_DC_ROLES; i++) 
	{
	  list->dc[i].dcProcessID = 0;
      list->dc[i].lastTimeHeardFrom = 0;
	}

	list->numberOfDCs = 0;
    list->msgQueueID = queueID;

	printf ("Shared-Memory ID is %d\n", sharedMemID);

    printf("Message queue opened: %d\n", list->msgQueueID);

    printf("sleeping for %d sec...\n", SECONDS_TO_SLEEP);

    sleep(SECONDS_TO_SLEEP);

    printf("listening...\n");
    fflush(stdout); // flush output to fix hang on sleep bug    

    // listen for messages
    while (!done)
    {   
        // receive a message 
        recMsg = msgrcv(list->msgQueueID, (void*)&msg, sizeof(MESSAGE), 0, 0);
        if (recMsg == NOT_FOUND)
        {
            printf("something bad happened!\n");
            // need to log
            break;
        }

        printf("Received message: %d, status %d\n", msg.PID, msg.status);

        // check if PID is new                
        int clientIndex = checkIDinMasterList(*list, msg.PID);
        time_t seconds = time(NULL);

        if (clientIndex == NOT_FOUND)
        {
            // client is new, add to MasterList
            printf("adding PID %d to MasterList\n", msg.PID);
            list->dc[list->numberOfDCs].dcProcessID = msg.PID;
            list->dc[list->numberOfDCs].lastTimeHeardFrom = seconds;
            list->numberOfDCs += 1;
        }
        else
        {   
            // only update last heard from time
            printf("updating PID  time %d\n", msg.PID);
            list->dc[clientIndex].lastTimeHeardFrom = seconds;
        }
        
        displayMasterList(list);

        // check for inactive machines (more than 35 seconds has passed with no message)

        // if offline status, remove from master list and log offline.

        // sleep for 1.5 seconds.
    }
    

    return 0;
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


void checkClients(DCInfo dc)
{

}