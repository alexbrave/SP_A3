/*
 *  FILE          : logMessage.c
 *  PROJECT       : SENG2030-21W-Sec1-System Programming - Assignment #3
 *  PROGRAMMER    : Andrey Takhtamirov, Alex Braverman
 *  FIRST VERSION : March 27, 2020 
 *  DESCRIPTION   : 
 *			This file contains 3 functions all related to logging. The main logging interface
 *          'logMessage', will use helper functions logMessageRegStatus() and logMessageSpecStatus()
 *          to log any kind of message that is needed in the program.
 *	
*/


#include "../inc/DC.h"

// Function prototypes
int logMessageRegStatus(int dcPID, FILE* logFile, int statusToLog, char* messageToLog, struct tm* to);
int logMessageSpecStatus(int dcPID, FILE* logFile, char* messageToLog, struct tm* to);


/*
* FUNCTION 		: logMessage
* DESCRIPTION 	: This function logs a message associated with a PID to the DC log file
* PARAMETERS 	: int dcPID	        : The PID of the DC that wants to log the message
*				  int statusToLog   : The status to log; all statuses found in DC.h 
* RETURNS 		: int : result indicating if logging succeeded or failed
* 
*/
int logMessage(int dcPID, int statusToLog)
{
    // Try to get the semaphore for the log file
    int getSemaphore = 0;
    int releaseSemaphore = 0;
    getSemaphore = getOrCreateLogSem();


    if(getSemaphore == OPERATION_FAILED)
    {
        // Unfortunately it looks like we were not able to get the semaphore, 
        // meaning we cannot even log that there is a problem, 
        // and must shut down silently
        return OPERATION_FAILED;
    }
    else
    {
        // open the log file 
        FILE* logFile = NULL;
        int closeFileStatus = 0;
        logFile = fopen(LOG_FILE_PATH, "a+");

        if (logFile == NULL)
        {
            // We can't open or create the log file, 
            // so must shutdown silently
            return OPERATION_FAILED;
        }
        
        // Initialize variables used for time, and get the current time
        struct tm* to;
        time_t currentTime;
        currentTime = time(NULL);
        to = localtime(&currentTime);

        // This switch statement will decide what log message to log based on the status provided
        switch (statusToLog)
        {
        // The following 7 logs are the regular statuses that are generated randomly
        case EVERYTHING_OK_INT:
            logMessageRegStatus(dcPID, logFile, EVERYTHING_OK_INT, EVERYTHING_OK_MSG, to);
            break;
        case HYDR_PRES_FAIL_INT:
            logMessageRegStatus(dcPID, logFile, HYDR_PRES_FAIL_INT, HYDR_PRES_FAIL_MSG, to);
            break;
        case SAFE_BUTTON_FAIL_INT:
            logMessageRegStatus(dcPID, logFile, SAFE_BUTTON_FAIL_INT, SAFE_BUTTON_FAIL_MSG, to);
            break;
        case NO_RAW_MATER_INT:
            logMessageRegStatus(dcPID, logFile, NO_RAW_MATER_INT, NO_RAW_MATER_MSG, to);
            break;
        case OPER_TMP_OUT_RNG_INT:
            logMessageRegStatus(dcPID, logFile, OPER_TMP_OUT_RNG_INT, OPER_TMP_OUT_RNG_MSG, to);
            break;
        case OPERATOR_ERROR_INT:
            logMessageRegStatus(dcPID, logFile, OPERATOR_ERROR_INT, OPERATOR_ERROR_MSG, to);
            break;
        case MACH_OFFLINE_INT:
            logMessageRegStatus(dcPID, logFile, MACH_OFFLINE_INT, MACH_OFFLINE_MSG, to);
            break;

        // The following statuses are special statuses to log
        case MACH_OFF_SHUTD_INT:
            logMessageSpecStatus(dcPID, logFile, MACH_OFF_SHUTD_MSG, to);
            break;
        case MSG_QUE_GONE_INT:
            logMessageSpecStatus(dcPID, logFile, MSG_QUE_GONE_MSG, to);
            break;
        case CANT_GET_MSG_KEY_INT:
            logMessageSpecStatus(dcPID, logFile, CANT_GET_MSG_KEY_MSG, to);
            break;

        default:
            return OPERATION_FAILED;
            closeFileStatus = fclose(logFile);
            releaseSemaphore = releaseLogSem();

            // If we weren't able to close the file or release the semaphore for some reason
            if(closeFileStatus == OPERATION_FAILED || releaseSemaphore == OPERATION_FAILED)
            {
                return OPERATION_FAILED;
            }
            break;
        }

        closeFileStatus = fclose(logFile);
        releaseSemaphore = releaseLogSem();

        // If we weren't able to close the file or release the semaphore for some reason
        if(closeFileStatus == OPERATION_FAILED || releaseSemaphore == OPERATION_FAILED)
        {
            return OPERATION_FAILED;
        }
    }

    // Otherwise, we were able to log everything successfully
    return OPERATION_SUCCESS;
}

/*
* FUNCTION 		: logMessageRegStatus
* DESCRIPTION 	: This function logs a message associated with a PID to the DC log file
* PARAMETERS 	: int dcPID             : the DC PID that will be indicated in the message
*                 FILE* logFile         : file pointer to log file 
*                 int statusToLog       : regular status that will be included in the log message
*                 char* messageToLog    : the text explaining the status 
*                 struct tm* to         : the time structure that will be used to add time and date to message
* RETURNS 		: int : result indicating if logging succeeded or failed
* 
*/
int logMessageRegStatus(int dcPID, FILE* logFile, int statusToLog, char* messageToLog, struct tm* to)
{
    fprintf(logFile, "[%d-%02d-%02d %02d:%02d:%02d] : DC [%d] - MSG SENT - Status %d (%s)\n", to->tm_year + 1900, to->tm_mon + 1, 
                to->tm_mday, to->tm_hour, to->tm_min, to->tm_sec, dcPID, statusToLog, messageToLog);
}

/*
* FUNCTION 		: logMessageSpecStatus
* DESCRIPTION 	: This function logs a message associated with a PID to the DC log file
* PARAMETERS 	: int dcPID             : the DC PID that will be indicated in the message
*                 FILE* logFile         : file pointer to log file 
*                 char* messageToLog    : the text of the log 
*                 struct tm* to         : the time structure that will be used to add time and date to message
* RETURNS 		: int : result indicating if logging succeeded or failed
* 
*/
int logMessageSpecStatus(int dcPID, FILE* logFile, char* messageToLog, struct tm* to)
{
    fprintf(logFile, "[%d-%02d-%02d %02d:%02d:%02d] : DC [%d] - %s\n", to->tm_year + 1900, to->tm_mon + 1, 
                to->tm_mday, to->tm_hour, to->tm_min, to->tm_sec, dcPID, messageToLog);
}
