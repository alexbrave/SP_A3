// ADD FILE HEADER COMMENT


#include "../inc/DC.h"

// ADD METHOD HEADER COMMENT
int sendMessage (pid_t dcPID, int msgQueID, int status)
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