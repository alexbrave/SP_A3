/*
 *  FILE          : logMessage.c
 *  PROJECT       : SENG2030-21W-Sec1-System Programming - Assignment #3
 *  PROGRAMMER    : Andrey Takhtamirov, Alex Braverman
 *  FIRST VERSION : March 27, 2020 
 *  DESCRIPTION   : 
 *			This file the logMessage function which will log the activity of the Data Corruptor,
 *          as well as any errors.
 *	
*/


#include "../inc/DX.h"


int logMessageSpecStatus(int dcPID, FILE* logFile, char* messageToLog, struct tm* to);


/*
* FUNCTION 		: logMessage
* DESCRIPTION 	: This function logs a message associated with a PID to the DC log file
* PARAMETERS 	: int dcPID	        : The PID of the DC that wants to log the message
*				  int statusToLog   : The status to log; all statuses found in DC.h 
*                 int WODAction     : This is the WOD action that the DX attempted to do
*                 int dcAffected    : The DC from the shared memory that was affected
* RETURNS 		: int : result indicating if logging succeeded or failed
* 
*/
int logMessage(int dcPID, int statusToLog, int WODAction, int dcAffected)
{

    // Get the current time
    struct tm* to;
    time_t currentTime;
    currentTime = time(NULL);
    to = localtime(&currentTime);

    // open the log file 
    FILE* logFile = NULL;
    int closeFileStatus = 0;
    logFile = fopen(LOG_FILE_PATH, "a+");
    if(logFile == NULL)
    {
        return OPERATION_FAILED;
    }

    switch (statusToLog)
    {
    case MSG_Q_DEL_SHUT_D:
        // Print the formatted message to the file
        fprintf(logFile, "[%d-%02d-%02d %02d:%02d:%02d] : DX deleted the msgQ – the DR/DCs can’t talk anymore - exiting\n", 
            to->tm_year + 1900, to->tm_mon + 1, to->tm_mday, to->tm_hour, to->tm_min, to->tm_sec);
        break;
    case NO_SUCH_PROCESS:
        fprintf(logFile, "[%d-%02d-%02d %02d:%02d:%02d] : No process with the PID [%d] could be found, no action taken\n", 
            to->tm_year + 1900, to->tm_mon + 1, to->tm_mday, to->tm_hour, to->tm_min, to->tm_sec, dcPID);
        break;
    case ACT_FAILED_QUIT:
        fprintf(logFile, "[%d-%02d-%02d %02d:%02d:%02d] : The DX failed in executing a WOD action, shutting down\n", 
            to->tm_year + 1900, to->tm_mon + 1, to->tm_mday, to->tm_hour, to->tm_min, to->tm_sec);
        break;
    case MSG_Q_NOT_THERE:
        fprintf(logFile, "[%d-%02d-%02d %02d:%02d:%02d] : Message queue was not available to be deleted, shutting down\n", 
            to->tm_year + 1900, to->tm_mon + 1, to->tm_mday, to->tm_hour, to->tm_min, to->tm_sec);
        break;
    case DC_KILL_SUCCESS:
        fprintf(logFile, "[%d-%02d-%02d %02d:%02d:%02d] : WOD Action %02d - DC-%02d [%d] TERMINATED\n", 
            to->tm_year + 1900, to->tm_mon + 1, to->tm_mday, to->tm_hour, to->tm_min, to->tm_sec, WODAction, dcAffected, dcPID);
        break;
    case CANT_KILL_PROC:
        fprintf(logFile, "[%d-%02d-%02d %02d:%02d:%02d] : Couldn't kill process with ID [%d], shutting down\n", 
            to->tm_year + 1900, to->tm_mon + 1, to->tm_mday, to->tm_hour, to->tm_min, to->tm_sec, dcAffected);
        break;
    case CANT_GET_MEM_ID:
        fprintf(logFile, "[%d-%02d-%02d %02d:%02d:%02d] : Couldn't get the shared memory ID after 100 tries, shutting down\n", 
            to->tm_year + 1900, to->tm_mon + 1, to->tm_mday, to->tm_hour, to->tm_min, to->tm_sec);
        break;
    case CANT_ATTACH_MEM:
        fprintf(logFile, "[%d-%02d-%02d %02d:%02d:%02d] : Couldn't attach to the shared memory, shutting down\n", 
            to->tm_year + 1900, to->tm_mon + 1, to->tm_mday, to->tm_hour, to->tm_min, to->tm_sec);
        break;
    

    default:
        closeFileStatus = fclose(logFile);
        // If we weren't able to close the file 
        if(closeFileStatus == OPERATION_FAILED)
        {
            return OPERATION_FAILED;
        }
        return OPERATION_FAILED;
        break;
    }

    closeFileStatus = fclose(logFile);
    // If we weren't able to close the file 
    if(closeFileStatus == OPERATION_FAILED)
    {
        return OPERATION_FAILED;
    }
}

int logMessageSpecStatus(int dcPID, FILE* logFile, char* messageToLog, struct tm* to)
{
    fprintf(logFile, "[%d-%02d-%02d %02d:%02d:%02d] : DC [%d] - %s\n", to->tm_year + 1900, to->tm_mon + 1, 
                to->tm_mday, to->tm_hour, to->tm_min, to->tm_sec, dcPID, messageToLog);
}
