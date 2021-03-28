/*
 *  FILE          : messageLogger.c
 *  PROJECT       : SENG2030-21W-Sec1-System Programming - Assignment #3
 *  PROGRAMMER    : Andrey Takhtamirov, Alex Braverman
 *  FIRST VERSION : March 26, 2020 
 *  DESCRIPTION   : 
 *			This file contains the logging functions for the DR application.
 *	            logMessage logs general messages (DC operations) and logError
                logs error messages (custom string).
*/
#include "../inc/DR.h"

/*
* FUNCTION 		: logMessage
* DESCRIPTION 	: Logs a message on normal operation, including the date
                    and time and DC information (number, status)
* PARAMETERS 	: int dcIndex
                    : the DC's index in the DC array in MasterList
                  int dcPID
                    : the DC's PID
                  int msgStatus
                    : the status received in DC's message
                  int dcStatus
                    : status of the DC (shutting down, non responsive, new)
* RETURNS 		: int : success/error (0/1)
*/
int logMessage(int dcIndex, int dcPID, int msgStatus, int dcStatus)
{
    struct tm *to;
    time_t currentTime;
    currentTime = time(NULL);

    // get the current time
    to = localtime(&currentTime);

    // array of status messages where the message's index is the status number
    char *messages[] = {EVERYTHING_OK_MSG, HYDR_PRES_FAIL_MSG,
                        SAFE_BUTTON_FAIL_MSG, NO_RAW_MATER_MSG, OPER_TMP_OUT_RNG_MSG,
                        OPERATOR_ERROR_MSG, MACH_OFFLINE_MSG};

    FILE *fp = NULL;

    fp = fopen(LOG_LOCATION, "a");

    if (fp == NULL)
    {
        printf("Error writing to log file!\n");
        return ERROR;
    }

    // index starts at 0 but we want our first client to be DC-01
    dcIndex += 1;

    if (dcStatus == NON_RESPONSIVE_DC_INT)
    {
        fprintf(fp, "[%d-%02d-%02d %02d:%02d:%02d] : DC-%.2d [%d] removed from master list - NON-RESPONSIVE\n", to->tm_year + 1900, to->tm_mon + 1,
                to->tm_mday, to->tm_hour, to->tm_min, to->tm_sec, dcIndex, dcPID);
    }
    else if (dcStatus == MACH_OFFLINE_INT)
    {
        fprintf(fp, "[%d-%02d-%02d %02d:%02d:%02d] : DC-%.2d [%d] has gone OFFLINE - removed from master list\n", to->tm_year + 1900, to->tm_mon + 1,
                to->tm_mday, to->tm_hour, to->tm_min, to->tm_sec, dcIndex, dcPID);
    }
    else if (dcStatus == NEW_DC_INT)
    {
        // new client (not in MasterList yet)
        fprintf(fp, "[%d-%02d-%02d %02d:%02d:%02d] : DC-%.2d [%d] added to the master list - NEW DC - Status %d (%s)\n", to->tm_year + 1900, to->tm_mon + 1,
                to->tm_mday, to->tm_hour, to->tm_min, to->tm_sec, dcIndex, dcPID, msgStatus, messages[msgStatus]);
    }
    else if (dcStatus == ALL_DCS_OFFLINE_INT)
    {
        // all DCs are offline (MasterList empty)
        fprintf(fp, "[%d-%02d-%02d %02d:%02d:%02d] %s\n", to->tm_year + 1900, to->tm_mon + 1,
                to->tm_mday, to->tm_hour, to->tm_min, to->tm_sec, ALL_DCS_OFFLINE_MSG);
    }
    else
    {
        // normal operation
        fprintf(fp, "[%d-%02d-%02d %02d:%02d:%02d] : DC-%.2d [%d] updated in the master list - MSG RECEIVED - Status %d (%s)\n", to->tm_year + 1900, to->tm_mon + 1,
                to->tm_mday, to->tm_hour, to->tm_min, to->tm_sec, dcIndex, dcPID, msgStatus, messages[msgStatus]);
    }

    fclose(fp);

    return SUCCESSFUL;
}

/*
* FUNCTION 		: logError
* DESCRIPTION 	: Logs an error message to a file, including the date and time.
* PARAMETERS 	: char *errorMessage
                    : the given message which will be logged
* RETURNS 		: int : success/error (0/1)
*/
int logError(char *errorMessage)
{
    struct tm *to;
    time_t currentTime;
    currentTime = time(NULL);
    to = localtime(&currentTime);

    FILE *fp = NULL;

    fp = fopen(LOG_LOCATION, "a");

    if (fp == NULL)
    {
        printf("Error writing to log file!\n");
        return ERROR;
    }

    fprintf(fp, "[%d-%02d-%02d %02d:%02d:%02d] %s\n", to->tm_year + 1900, to->tm_mon + 1,
            to->tm_mday, to->tm_hour, to->tm_min, to->tm_sec, errorMessage);

    fclose(fp);

    return SUCCESSFUL;
}
