/*
 *  FILE          : checkQueExists.c 
 *  PROJECT       : SENG2030-21W-Sec1-System Programming - Assignment #3
 *  PROGRAMMER    : Andrey Takhtamirov, Alex Braverman
 *  FIRST VERSION : March 27, 2020 
 *  DESCRIPTION   : 
 *			This file contains a function that will check if the queue with the 
 *          provided ID exists.
 *	
*/


#include "../inc/DX.h"

/*
* FUNCTION 		: checkQueExists
* DESCRIPTION 	: Checks the existence of a message queue
* PARAMETERS 	: int msgQueID : the ID of the messsage queue 
* RETURNS 		: int : returns whether finding the queue succeeded or not
*/
int checkQueExists(int msgQueID)
{
    // We're going to send an empty message to see if the queue exists,
    // if this fails, then we know that the queue doesn't exist

    // Instantiate a MESSAGE variable
	MESSAGE msg;

    // Get the size of the MESSAGE variable minus the long
	int sizeofdata = sizeof (MESSAGE) - sizeof (long);

    // Set type to 0, so that the DR knows to ignore it
	msg.type = DC_2_INDEX;

    // Use the PID that main() supplied in the arguments
	msg.PID = DC_2_INDEX;

    // Use the status that main supplied
	msg.status = DC_2_INDEX;

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