#include "../inc/DR.h"

int main(void)
{
    key_t msgKey;
    bool done = false;
    
    int recMsg;
    int queueID;

    MESSAGE msg;

    // create key for message queue
    msgKey = ftok(CURRENT_DIRECTORY, AGREED_UPON_VALUE);
    if (msgKey == MSG_QUEUE_NOT_FOUND)
    {
        printf("ERROR Key could not be created!\n");
        // need to log
        fflush(stdout);
        return 1;
    }

    // check if message queue already exists, if not, make a new queue
    queueID = msgget(msgKey, CHECK_MSG_QUEUE_EXISTS);

    if (queueID == MSG_QUEUE_NOT_FOUND)
    {
        printf("Existing message queue not found\n");
        queueID = msgget(msgKey, IPC_CREAT | 0660);

        if (queueID == MSG_QUEUE_NOT_FOUND)
        {
            printf("Error creating message queue!\n");
            // need to log
            return 1;
        }
        
    }
    
    printf("Message queue opened: %d\n", queueID);

    // listen for messages
    while (!done)
    {   
        // receive a message 
        // for me: need to use the right size
        recMsg = msgrcv(queueID, (void*)&msg, 100, 0, 0);

        if (recMsg == -1)
        {
            // need to log
            break;
        }

        printf("Received message: %d, status %d\n", msg.PID, msg.status);
    }
    

    return 0;
}
