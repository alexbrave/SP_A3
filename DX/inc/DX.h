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
#include <sys/shm.h>
#include <signal.h>



// POSSIBLY ADD COMMENTS/EXPLANATIONS FOR EACH CONSTANT

#define OPERATION_FAILED  -1
#define OPERATION_SUCCESS 0
#define MIN_SLEEP         10
#define MAX_SLEEP         30


// These constants are for the shared memory
#define AGREED_UPON_VALUE   16535
#define AGREED_UPON_PATH    "."
#define SHARED_MEM_SIZE     168
#define CHECK_SHR_MEM_EXIST 0
#define CANT_ATTACH_SLEEP   10
#define MAX_ATTACH_RETRIES  100


// WOD Constants
#define NUM_OF_WOD_ACTS     21 
#define CHECK_PROC_EXISTS   0   // this flag is used with the kill function to check if a 
                                // process with a given process ID exists

// WOD Result Statuses 
// these statuses will be returned be the function attempting to execute a WOD action
#define MSG_Q_DEL_SHUT_D    2 // message successfully queue deleted, so shut down
#define NO_SUCH_PROCESS     3 // no such process could be found to execute action on
#define ACT_FAILED_QUIT     4 // the process was found, but the action failed, so shut down
#define MSG_Q_NOT_THERE     5 // we were going to delete the message queue, 
                              // but it's already gone, so shut down
#define DC_KILL_SUCCESS     6

// WOD Target Processes Indexes
#define DC_1_INDEX    0
#define DC_2_INDEX    1
#define DC_3_INDEX    2
#define DC_4_INDEX    3
#define DC_5_INDEX    4
#define DC_6_INDEX    5
#define DC_7_INDEX    6
#define DC_8_INDEX    7
#define DC_9_INDEX    8
#define DC_10_INDEX   9



// Following are the definitions for data in the masterlist provided with the assignment
#define MAX_DC_ROLES 10

typedef struct
{
    pid_t dcProcessID;
    time_t lastTimeHeardFrom;
} DCInfo;

typedef struct
{
    int msgQueueID;
    int numberOfDCs;
    DCInfo dc[MAX_DC_ROLES];
} MasterList;



// Function prototypes
int logMessage(int dcPID, int statusToLog, int WODAction, int dcAffected);
int genRandSleep(void);
int checkQueExists(int msgQueID);
int executeWODAct(MasterList* masterList);



// Special statuses for logging
#define SHUTDOWN_INT 7


// Temp log file for debugging
#define LOG_FILE_PATH "/tmp/dataCorruptor.log"
#define MAX_LOG_LEN 100


// this is for the msgget function to indicate that we want to check if the
// message queue already exists, rather than create a new one
#define CHECK_MSG_Q_EXISTS 0
// This is part of the design of our program, since the Data Corruptor wants to check if the 
// message queue exists, but doesn't want the data reader to do anything with our test message
// we set the type of the message to 0, which DR knows to ignore 
#define IGNORE_MSG_TYPE    0


// MESSAGESTRUCT struct definition
typedef struct MESSAGESTRUCT 
{
	// This will be set to 0 (IGNORE_MSG_TYPE), since we want our messages to be ignored
	long type;

	// In this program/system, we only want DC's to send their PID and their status
	pid_t PID;	
	int status;	
	
} MESSAGE;





#endif