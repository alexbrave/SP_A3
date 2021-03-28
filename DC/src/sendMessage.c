/*
 *  FILE          : sendMessage.c
 *  PROJECT       : SENG2030-21W-Sec1-System Programming - Assignment #3
 *  PROGRAMMER    : Andrey Takhtamirov, Alex Braverman
 *  FIRST VERSION : March 27, 2020 
 *  DESCRIPTION   : 
 *			This file contains a function that will attempt to send a message to 
 *          the data reader via a message queue.
 *	
*/

#include "../inc/DC.h"

/*
* FUNCTION 		: sendMessage
* DESCRIPTION 	: Send a message struct with the provided status to the 
*                 queue with the provided ID
* PARAMETERS 	: pid_t dcPID   : The PID of the process sending the message
*                 int msgQueID  : The ID of the message queue that we are sending over
*                 int status    : The status that we are sending to the DR
* RETURNS 		: int : returns whether the operation succeeded or failed
*/
int sendMessage(pid_t dcPID, int msgQueID, int status)
{
    // Instantiate a MESSAGE variable
	MESSAGE msg;

    // Get the size of the MESSAGE variable minus the long
	int sizeofdata = sizeof (MESSAGE) - sizeof (long);

    // Set type to default, since we're not using it meaningfully
	msg.type = DEFAULT_TYPE;

    // Use the PID that main() supplied in the arguments
	msg.PID = dcPID;

    // Use the status that main supplied
	msg.status = status;

	// Send the message over the message queue and check return
	if(msgsnd (msgQueID, (void *)&msg, sizeofdata, 0) == OPERATION_FAILED)
    {
        return OPERATION_FAILED;
    }
    else
    {
        return OPERATION_SUCCESS;
    }
}