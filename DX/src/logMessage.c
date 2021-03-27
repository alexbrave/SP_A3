// ADD FILE HEADER COMMENT


#include "../inc/DX.h"

// ADD METHOD HEADER COMMENT
int logMessage(int dcPID, int statusToLog, int WODAction, int dcAffected)
{
    /* There are only a few types of messages we can log:    1) Successfully killed a process
    2) The message queue was successfully deleted
    3) The message queue could not be deleted because it's gone
    4) We were not able to execute our action so we are shutting down
    */

    struct tm* to;
    time_t currentTime;
    currentTime = time(NULL);
    to = localtime(&currentTime);

   // open the log file 
    FILE* logFile = NULL;
    int closeFileStatus = 0;
    logFile = fopen(LOG_FILE_PATH, "a+");
    // ADD LOGIC FOR IF logFile == NULL

    switch (statusToLog)
    {
    case MSG_Q_DEL_SHUT_D:
        // Print the formatted message to the file
        fprintf(logFile, "[%d-%02d-%02d %02d:%02d:%02d] : DX deleted the msgQ – the DR/DCs can’t talk anymore - exiting\n", 
            to->tm_year + 1900, to->tm_mon + 1, to->tm_mday, to->tm_hour, to->tm_min, to->tm_sec);
        break;
    case NO_SUCH_PROCESS:
        // Print the formatted message to the file
        fprintf(logFile, "[%d-%02d-%02d %02d:%02d:%02d] : No process with the PID [%d] could be found, no action taken\n", 
            to->tm_year + 1900, to->tm_mon + 1, to->tm_mday, to->tm_hour, to->tm_min, to->tm_sec, dcPID);
        break;
    case ACT_FAILED_QUIT:
        // Print the formatted message to the file
        fprintf(logFile, "[%d-%02d-%02d %02d:%02d:%02d] : The DX failed in executing a WOD action, shutting down\n", 
            to->tm_year + 1900, to->tm_mon + 1, to->tm_mday, to->tm_hour, to->tm_min, to->tm_sec);
        break;
    case MSG_Q_NOT_THERE:
        // Print the formatted message to the file
        fprintf(logFile, "[%d-%02d-%02d %02d:%02d:%02d] : Message queue was not available to be deleted, shutting down\n", 
            to->tm_year + 1900, to->tm_mon + 1, to->tm_mday, to->tm_hour, to->tm_min, to->tm_sec);
        break;
    case DC_KILL_SUCCESS:
        // Print the formatted message to the file
        // WOD Action 11 – DC-01 [7565] TERMINATED
        fprintf(logFile, "[%d-%02d-%02d %02d:%02d:%02d] : WOD Action %d - DC-%02d [%d] TERMINATED\n", 
            to->tm_year + 1900, to->tm_mon + 1, to->tm_mday, to->tm_hour, to->tm_min, to->tm_sec, WODAction, dcAffected, dcPID);
        break;
    
    
    default:
        break;
    }
    

   // We will use a case statement to log messages
}
