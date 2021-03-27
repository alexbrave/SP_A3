// ADD FILE HEADER COMMENT


#include "../inc/DX.h"

// These functions should only be used by executeWODAct(), 
// thus they are declared and defined here, and not in the header file
int attemptToKillProcess(int dcPID, int WODAction, int dcAffected);
int attemptToDeleteMsgQ(int msgQueueID);

// POSSIBLY CAPITALIZE LATER
#define doNothingA 0 // do nothing
#define killDC01A 1 // kill DC-01 (if it exists)
#define killDC03A 2 // kill DC-03 (if it exists)
#define killDC02A 3 // kill DC-02 (if it exists)
#define killDC01B 4 // kill DC-01 (if it exists)
#define killDC03B 5 // kill DC-03 (if it exists)
#define killDC02B 6 // kill DC-02 (if it exists)
#define killDC04A 7 // kill DC-04 (if it exists)
#define doNothingB 8 // do nothing
#define killDC05A 9 // kill DC-05 (if it exists)
#define delMsgQueA 10 // delete the message queue being used between DCs and DR
#define killDC01C 11 // kill DC-01 (if it exists)
#define killDC06A 12 // kill DC-06 (if it exists)
#define killDC02C 13 // kill DC-02 (if it exists)
#define killDC07A 14 // kill DC-07 (if it exists)
#define killDC03C 15 // kill DC-03 (if it exists)
#define killDC08A 16 // kill DC-08 (if it exists)
#define delMsgQueB 17 // delete the message queue being used between the DCs and DR
#define killDC09A 18 // kill DC-09 (if it exists)
#define doNothingC 19 // do nothing
#define killDC10A 20 // kill DC-10 (if it exists)

// ADD METHOD HEADER COMMENT
int executeWODAct(MasterList* masterList)
{
    // First we want to generate a random action between 0 and 20
    int action = 0;
    time_t secondsSinceEpoch = 0;

      
    // Intialize random number generator
    srand((unsigned) time(&secondsSinceEpoch));

    // Get random status
    action = rand() % NUM_OF_WOD_ACTS;


    // Many of these actions attempt to kill a process,
    // if there is no such process, DR is assumed to have set
    // it's DC's PID in the masterlist to 0
    switch (action)
    {
    case doNothingA: // Action 0
        return OPERATION_SUCCESS;
        break;
    case killDC01A: // Action 1
        return attemptToKillProcess(masterList->dc[DC_1_INDEX].dcProcessID, killDC01A, DC_1_INDEX + 1);
        break;
    case killDC03A: // Action 2
        return attemptToKillProcess(masterList->dc[DC_3_INDEX].dcProcessID, killDC03A, DC_3_INDEX + 1);
        break;
    case killDC02A: // Action 3
        return attemptToKillProcess(masterList->dc[DC_2_INDEX].dcProcessID, killDC02A, DC_2_INDEX + 1);
        break;
    case killDC01B: // Action 4
        return attemptToKillProcess(masterList->dc[DC_1_INDEX].dcProcessID, killDC01B, DC_1_INDEX + 1);
        break;
    case killDC03B: // Action 5
        return attemptToKillProcess(masterList->dc[DC_3_INDEX].dcProcessID, killDC03B, DC_3_INDEX + 1);
        break;
    case killDC02B: // Action 6
        return attemptToKillProcess(masterList->dc[DC_2_INDEX].dcProcessID, killDC02B, DC_2_INDEX + 1);
        break;
    case killDC04A: // Action 7
        return attemptToKillProcess(masterList->dc[DC_4_INDEX].dcProcessID, killDC04A, DC_4_INDEX + 1);
        break;
    case doNothingB: // Action 8
        return OPERATION_SUCCESS;
        break;
    case killDC05A: // Action 9
        return attemptToKillProcess(masterList->dc[DC_5_INDEX].dcProcessID, killDC05A, DC_5_INDEX + 1);
        break;
    case delMsgQueA: // Action 10
        return attemptToDeleteMsgQ(masterList->msgQueueID);
        break;
    case killDC01C: // Action 11
        return attemptToKillProcess(masterList->dc[DC_1_INDEX].dcProcessID, killDC01C, DC_1_INDEX + 1);
        break;
    case killDC06A: // Action 12
        return attemptToKillProcess(masterList->dc[DC_6_INDEX].dcProcessID, killDC06A, DC_6_INDEX + 1);
        break;
    case killDC02C: // Action 13
        return attemptToKillProcess(masterList->dc[DC_2_INDEX].dcProcessID, killDC02C, DC_2_INDEX + 1);
        break;
    case killDC07A: // Action 14
        return attemptToKillProcess(masterList->dc[DC_7_INDEX].dcProcessID, killDC07A, DC_7_INDEX + 1);
        break;
    case killDC03C: // Action 15
        return attemptToKillProcess(masterList->dc[DC_3_INDEX].dcProcessID, killDC03C, DC_3_INDEX + 1);
        break;
    case killDC08A: // Action 16
        return attemptToKillProcess(masterList->dc[DC_8_INDEX].dcProcessID, killDC08A, DC_8_INDEX + 1);
        break;
    case delMsgQueB: // Action 17
        return attemptToDeleteMsgQ(masterList->msgQueueID);
        break;
    case killDC09A: // Action 18
        return attemptToKillProcess(masterList->dc[DC_9_INDEX].dcProcessID, killDC09A, DC_9_INDEX + 1);
        break;
    case doNothingC: // Action 19
        return OPERATION_SUCCESS;
        break;
    case killDC10A: // Action 20
        return attemptToKillProcess(masterList->dc[DC_10_INDEX].dcProcessID, killDC10A, DC_10_INDEX + 1);
        break;

    default:
        return OPERATION_FAILED;
        break;
    }
    

}

// ADD FUNCTION HEADER
int attemptToKillProcess(int dcPID, int WODAction, int dcAffected)
{
    int resultOfWODAct = 0;
    resultOfWODAct = kill(dcPID, CHECK_PROC_EXISTS);
        if(resultOfWODAct == OPERATION_FAILED)
        {
            // The process does not exist, so exit
            return NO_SUCH_PROCESS;
        }
        else
        {
            // Otherwise we know that the process exists and we can send it the SIGHUP signal
            resultOfWODAct = kill(dcPID, SIGHUP);
            if (resultOfWODAct == OPERATION_FAILED)
            {
                return ACT_FAILED_QUIT;
            }
            // LOG THAT PROCESS HAS BEEN KILLED
            return DC_KILL_SUCCESS;
        }
}

//  FUNCTION HEADER
int attemptToDeleteMsgQ(int msgQueueID)
{
    // First we need to check if the message queue exists
    int WODActResult = 0;
    WODActResult = checkQueExists(msgQueueID);

    if (WODActResult == OPERATION_FAILED)
    {
        // Looks like the message queue does not exist!
        return MSG_Q_NOT_THERE;
    }
    else
    {
        WODActResult = msgctl(msgQueueID, IPC_RMID, NULL);
        if(WODActResult == OPERATION_SUCCESS)
        {
            // We were able to successfully delete the message queue!
            // Now it's time to let the calling function know to shut down.
            return MSG_Q_DEL_SHUT_D;
        }
        else
        {
            // Hmm, the message queue seems to be there, but we were not able to delete it
            return ACT_FAILED_QUIT;
        }
    }
}