/*
 *  FILE          : dc.h
 *  PROJECT       : SENG2030-21W-Sec1-System Programming - Assignment #3
 *  PROGRAMMER    : Andrey Takhtamirov, Alex Braverman
 *  FIRST VERSION : March 24, 2020 
 *  DESCRIPTION   : 
 *	        This file contains some constants and function prototypes for the
 *          Data Creator program.
*/

#ifndef DC_H
#define DC_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>
#include <sys/sem.h>
#include <time.h>


// POSSIBLY ADD COMMENTS/EXPLANATIONS FOR EACH CONSTANT
#define AGREED_UPON_VALUE 100
#define CURRENT_DIRECTORY "."
#define OPERATION_FAILED  -1
#define OPERATION_SUCCESS 0
#define MIN_SLEEP         10
#define MAX_SLEEP         30

// this is for the msgget function to indicate that we want to check if the
// message queue already exists, rather than create a new one
#define CHECK_MSG_Q_EXISTS 0 

#define MSG_Q_NOT_EXIST_SLEEP 10


// Function prototypes
int sendMessage (pid_t dcPID, int msgQueID, int status);
int logMessage(int dcPID, int statusToLog, char* messageToLog);
int genRandStatus(void);
int getOrCreateLogSem(void);
int genRandSleep(void);
// int sendMessage (pid_t dcPID, int msgQueID, int status);
int releaseLogSem(void);




// Status Constants
#define NUM_OF_STATUSES 7
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

// Special statuses for logging
#define SHUTDOWN_INT 7
#define MACH_OFF_SHUTD_MSG "Machine Off-Line message issued, shutting down"
#define MSG_QUE_GONE_MSG "Could not send message over que, it may be gone, shutting down"



// Log file path
// #define LOG_FILE_PATH "/tmp/dataCreator.log"

// Temp log file for debugging
#define LOG_FILE_PATH "/tmp/dataCreator.log"
#define MAX_LOG_LEN 100

// Log Message Entries
#define LOG_MSG_QUE_GONE 1 // this is for the main loop if DC discovers that msg queue is gone
#define LOG_GET_MSG_KEY_FAILED 2
#define LOG_MSG_QUE_NOT_THERE 3 // before the main loop if the DC can't get to message queue
#define LOG_MACH_SHUT_DOWN 4

// Semaphore Constants
#define SEM_FTOK_ID 123456789
#define NUM_OF_SEMS 1
#define CHECK_SEM_EXISTS 0
#define SEM_INITAL_VALUE 1
#define NUM_SOP_STRUCTS 1


// Constants used with MESSAGESTRUCT
#define DEFAULT_TYPE 1

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


#endif