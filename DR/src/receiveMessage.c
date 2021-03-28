/*
 *  FILE          : receiveMessage.c
 *  PROJECT       : SENG2030-21W-Sec1-System Programming - Assignment #3
 *  PROGRAMMER    : Andrey Takhtamirov, Alex Braverman
 *  FIRST VERSION : March 26, 2020 
 *  DESCRIPTION   : 
 *			This file contains the function needed to receive messages via
 *              a message queue. The MESSAGE struct will be populated with
 *              the received message.
*/
#include "../inc/DR.h"

/*
* FUNCTION 		: removeClient
* DESCRIPTION 	: Receives a message via message queue and populate MasterList
                    and MESSAGE structs
* PARAMETERS 	: MasterList *list
                    : pointer to MasterList (store DC information)
                  MESSAGE *msg
                    : pointer to MESSAGE (will be received via message queue)
* RETURNS 		: int : success/not found (0/-1)
                    "not found" indicates an error reading the message queue
*/
int receiveMessage(MasterList *list, MESSAGE *msg)
{
    int recMsg = 0;

    // receive a message
    recMsg = msgrcv(list->msgQueueID, (void *)msg, sizeof(MESSAGE), 0, 0);
    if (recMsg == NOT_FOUND)
    {
        return NOT_FOUND;
    }

    // only add to MasterList if message is from DC
    if (msg->type == DC_MESSAGE_TYPE)
    {
        // check if PID is new
        int clientIndex = checkIDinMasterList(*list, msg->PID);
        time_t seconds = time(NULL);

        if (clientIndex == NOT_FOUND)
        {
            // client is new, add to MasterList
            list->dc[list->numberOfDCs].dcProcessID = msg->PID;
            list->dc[list->numberOfDCs].lastTimeHeardFrom = seconds;

            // only log existing message if it's not a shutdown message.
            // shutdown messages will be logged when they're processed by checkStatus.
            if (msg->status != MACH_OFFLINE_INT)
            {
                logMessage(list->numberOfDCs, msg->PID, msg->status, NEW_DC_INT);
            }

            // increment DC counter
            list->numberOfDCs += 1;
        }
        else
        {
            // only update last heard from time
            list->dc[clientIndex].lastTimeHeardFrom = seconds;

            // only log existing message if it's not a shutdown message.
            // shutdown messages will be logged when they're processed by checkStatus.
            if (msg->status != MACH_OFFLINE_INT)
            {
                logMessage(clientIndex, msg->PID, msg->status, EXISTING_DC_INT);
            }
        }
    }

    return SUCCESSFUL;
}
