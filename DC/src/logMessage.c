// ADD FILE HEADER COMMENT


#include "../inc/DC.h"

// ADD METHOD HEADER COMMENT
int logMessage(int dcPID, int statusToLog, char* messageToLog)
{
    // Try to get the semaphore for the log file
    int getSemaphore = 0;
    int releaseSemaphore = 0;
    getSemaphore = getOrCreateLogSem();


    if(getSemaphore == OPERATION_FAILED)
    {
        // Unfortunately it looks like despite an honest attempt,
        // we were not able to get the semaphore, meaning we cannot
        // even log that there is a problem, and must shut down silently

        return OPERATION_FAILED;
    }
    else
    {
        // open the log file 
        FILE* logFile = NULL;
        int closeFileStatus = 0;
        logFile = fopen(LOG_FILE_PATH, "a+");
        // ADD LOGIC FOR IF logFile == NULL

        struct tm* to;
        time_t currentTime;
        currentTime = time(NULL);
        to = localtime(&currentTime);

        
        // Here the DC has sent a regular status with it's associated message
        if(statusToLog >= EVERYTHING_OK_INT && statusToLog <= MACH_OFFLINE_INT)
        {
            // Print the formatted message to the file
            fprintf(logFile, "[%d-%02d-%02d %02d:%02d:%02d] : DC [%d] - MSG SENT - Status %d (%s)\n", to->tm_year + 1900, to->tm_mon + 1, 
                to->tm_mday, to->tm_hour, to->tm_min, to->tm_sec, dcPID, statusToLog, messageToLog);

            // PRINT STATEMENT FOR DEBUGGING
            // printf("[%d-%02d-%02d %02d:%02d:%02d] : DC [%d] - MSG SENT - Status %d (%s)", to->tm_year + 1900, to->tm_mon + 1, 
            //     to->tm_mday, to->tm_hour, to->tm_min, to->tm_sec, dcPID, statusToLog, messageToLog);
        }

        // Otherwise, we received a special log request from main, likely indicating that we are shutting down,
        // possibly because we issued "Machine is Off-Line" message, or something went wrong!
        else
        {
            fprintf(logFile, "[%d-%02d-%02d %02d:%02d:%02d] : DC [%d] - SHUT DOWN - No Status (%s))\n", to->tm_year + 1900, to->tm_mon + 1, 
                to->tm_mday, to->tm_hour, to->tm_min, to->tm_sec, dcPID, messageToLog);
        }

        closeFileStatus = fclose(logFile);

        releaseSemaphore = releaseLogSem();

        printf("\n\nThe semapphore was released with status %d\n", releaseSemaphore);
        
    }



    return 0;
}
