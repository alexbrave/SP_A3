/*
 *  FILE          : DR.h
 *  PROJECT       : SENG2030-21W-Sec1-System Programming - Assignment #3
 *  PROGRAMMER    : Andrey Takhtamirov, Alex Braverman
 *  FIRST VERSION : March 26, 2020 
 *  DESCRIPTION   : 
 *			This file contains the function prototypes and constants for the
 *              DR program, used by DR.c, receiveMessage.c, checkIDinMasterList.c,
 *              manageClients.c, and messageLogger.c.
*/
#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/shm.h>
#include <stdbool.h>
#include <unistd.h>
#include <time.h>
#include <string.h>

// "secret" constants and keys
#define CHECK_MSG_QUEUE_EXISTS 0
#define AGREED_UPON_VALUE 123456789
#define CURRENT_DIRECTORY "."
#define SHARED_MEMORY_KEY 16535

#define CREATE_VALUE 0660

// error/success codes
#define NOT_FOUND -1
#define SUCCESSFUL 0
#define ERROR 1

// sleep rates
#define SECONDS_TO_SLEEP_ON_STARTUP 1
#define SECONDS_TO_SLEEP_BETWEEN_MESSAGES 1.5

// limit for client inactivity
#define INACTIVE_CLIENT_TIME_SECONDS 35

// msg constants
#define EVERYTHING_OK_INT 0
#define EVERYTHING_OK_MSG "Everything is OKAY"
#define HYDR_PRES_FAIL_INT 1
#define HYDR_PRES_FAIL_MSG "Hydraulic Pressure Failure"
#define SAFE_BUTTON_FAIL_INT 2
#define SAFE_BUTTON_FAIL_MSG "Safety Button Failure"
#define NO_RAW_MATER_INT 3
#define NO_RAW_MATER_MSG "No Raw Material in the Process"
#define OPER_TMP_OUT_RNG_INT 4
#define OPER_TMP_OUT_RNG_MSG "Operating Temperature Out of Range"
#define OPERATOR_ERROR_INT 5
#define OPERATOR_ERROR_MSG "Operator Error"
#define MACH_OFFLINE_INT 6
#define MACH_OFFLINE_MSG "Machine is Off-line"

// dc action values
#define EXISTING_DC_INT 0
#define NON_RESPONSIVE_DC_INT 7
#define NEW_DC_INT 8
#define DC_UPDATED_INT 9
#define ALL_DCS_OFFLINE_INT 10
#define ALL_DCS_OFFLINE_MSG "All DCs have gone offline or terminated - DR TERMINATING"

#define DC_MESSAGE_TYPE 1 // type for DC messages
#define DX_MESSAGE_TYPE 0 // type for DX messages

// MESSAGESTRUCT struct definition
typedef struct MESSAGESTRUCT
{
    // This will be set to 1, since we're not really interested in the order
    // in which the Data Reader will read the messages
    long type;

    // In this program/system, we only want DC's to send their PID and their status
    pid_t PID;
    int status;

} MESSAGE;

// given by sean from assignment specifications
#define MAX_DC_ROLES 10

typedef struct
{
    pid_t dcProcessID;
    long lastTimeHeardFrom;
} DCInfo;

typedef struct
{
    int msgQueueID;
    int numberOfDCs;
    DCInfo dc[MAX_DC_ROLES];
} MasterList;

//  logging file location
#define LOG_LOCATION "/tmp/dataMonitor.log"

// function prototypes
int receiveMessage(MasterList *list, MESSAGE *msg);
int checkIDinMasterList(MasterList list, int clientID);
int checkInactiveClients(MasterList *list);
void reorder(MasterList *list);
int removeClient(MasterList *list, int clientIndex);
int checkStatus(MasterList *list, MESSAGE msg);

// logging function prototypes
int logMessage(int dcIndex, int dcPID, int msgStatus, int dcStatus);
int logError(char *errorMessage);
