#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/shm.h>
#include <stdbool.h>
#include <unistd.h>
#include <time.h>

#include <string.h>

// msg queue constants
#define CHECK_MSG_QUEUE_EXISTS 0

#define AGREED_UPON_VALUE 123456789
#define CURRENT_DIRECTORY "."

#define SHARED_MEMORY_KEY 16535

#define NOT_FOUND -1
#define SUCCESSFUL 0

#define SECONDS_TO_SLEEP_ON_STARTUP 1
#define SECONDS_TO_SLEEP_BETWEEN_MESSAGES 1.5

#define INACTIVE_CLIENT_TIME_SECONDS 35

// msg values
#define ALL_OK 0
#define HYDRAULIC_PRESSURE_FAILURE 1
#define SAFETY_BUTTON_FAILURE 2
#define NO_RAW_MATERIAL_IN_THE_PROCESS 3
#define OPERATING_TEMP_OUT_OF_RANGE 4
#define OPERATOR_ERROR 5
#define MACHINE_OFFLINE 6


#define DC_MESSAGE_TYPE 1
#define DX_MESSAGE_TYPE 0

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



//  logging stuff
#define LOG_LOCATION "/tmp/dataMonitor.log"
#define LOG_SUCCESS 0
#define LOG_ERROR -1
