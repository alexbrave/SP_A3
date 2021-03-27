// ADD FILE HEADER COMMENT


#include "../inc/DX.h"

// ADD METHOD HEADER COMMENT
int checkQueExists(int msgQueID)
{
    // We're going to send an empty message to see if the queue exists,
    // if this fails, then we know that the queue doesn't exist

    // Instantiate a MESSAGE variable
	MESSAGE msg;

    // Get the size of the MESSAGE variable minus the long
	int sizeofdata = sizeof (MESSAGE) - sizeof (long);

    // Set type to 0, so that the DR knows to ignore it
	msg.type = CHECK_MSG_Q_EXISTS;

    // Use the PID that main() supplied in the arguments
	msg.PID = CHECK_MSG_Q_EXISTS;

    // Use the status that main supplied
	msg.status = CHECK_MSG_Q_EXISTS;

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