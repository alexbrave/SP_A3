/*
 *  FILE          : manageClients.c
 *  PROJECT       : SENG2030-21W-Sec1-System Programming - Assignment #3
 *  PROGRAMMER    : Andrey Takhtamirov, Alex Braverman
 *  FIRST VERSION : March 26, 2020 
 *  DESCRIPTION   : 
 *			This file contains the functions needed to check and manage DCs
 *              for the DR program. It contains functions which scan, reorder,
 *              and remove dcs from the dc array inside MasterList.
*/
#include "../inc/DR.h"

/*
* FUNCTION 		: checkInactiveClients
* DESCRIPTION 	: Checks all DCs for inactivity, removing inactive clients.
                    returns -1 if the MasterList is empty after removal.
* PARAMETERS 	: MasterList *list
                    : pointer to MasterList which contains the DCs
* RETURNS 		: int : success/shutdown state envoked (0/-1)
*/
int checkInactiveClients(MasterList *list)
{
    time_t currentTime = time(NULL);
    int i = 0;

    for (i = 0; i < list->numberOfDCs; i++)
    {
        // if last heard from time is more than 35 seconds less than current time,
        // client is inactive
        if (currentTime - list->dc[i].lastTimeHeardFrom > INACTIVE_CLIENT_TIME_SECONDS)
        {
            logMessage(i, list->dc[i].dcProcessID, MACH_OFFLINE_INT, NON_RESPONSIVE_DC_INT);
            return removeClient(list, i);
        }
    }
}

/*
* FUNCTION 		: checkStatus
* DESCRIPTION 	: Checks the status of an incoming message and removes the DC if OFFLINE
                    returns -1 if the MasterList is empty after removal.
* PARAMETERS 	: MasterList *list
                    : pointer to MasterList which contains the DCs
                  MESSAGE msg
                    : msg struct which contains the status
* RETURNS 		: int : success/shutdown state envoked (0/-1)
*/
int checkStatus(MasterList *list, MESSAGE msg)
{
    int i = 0;

    if (msg.status == MACH_OFFLINE_INT)
    {
        // find and remove offline DC from MasterList
        for (i = 0; i < list->numberOfDCs; i++)
        {
            if (list->dc[i].dcProcessID == msg.PID)
            {
                // this is our offline client
                logMessage(i, list->dc[i].dcProcessID, MACH_OFFLINE_INT, MACH_OFFLINE_INT);
                return removeClient(list, i);
            }
        }
    }
}

/*
* FUNCTION 		: removeClient
* DESCRIPTION 	: Removes client of given index from MasterList
                    returns -1 if the MasterList is empty after removal.
* PARAMETERS 	: MasterList *list
                    : pointer to MasterList which contains the DCs
                  int clientIndex
                    : index of the client to remove
* RETURNS 		: int : success/shutdown state envoked (0/-1)
*/
int removeClient(MasterList *list, int clientIndex)
{
    // remove DC from MasterList struct
    list->dc[clientIndex].dcProcessID = 0;
    list->dc[clientIndex].lastTimeHeardFrom = 0;

    // collpase the MasterList struct (reorder to make all elements adjacent)
    reorder(list);

    // update number of DCs
    list->numberOfDCs -= 1;

    if (list->numberOfDCs == 0)
    {
        logMessage(clientIndex, list->dc[clientIndex].dcProcessID, ALL_DCS_OFFLINE_INT, ALL_DCS_OFFLINE_INT);
        return NOT_FOUND;
    }

    return SUCCESSFUL;
}

/*
* FUNCTION 		: reorder
* DESCRIPTION 	: Reorders the MasterList (removing empty elements between DCs)
* PARAMETERS 	: MasterList *list
                    : pointer to MasterList which contains the DCs
* RETURNS 		: void
*/
void reorder(MasterList *list)
{
    int i = 0;
    int j = 0;

    for (i = 0; i < list->numberOfDCs; i++)
    {
        // find empty DC
        if (list->dc[i].dcProcessID == 0 && list->dc[i].lastTimeHeardFrom == 0)
        {
            // find the next non empty element
            for (j = i + 1; j < list->numberOfDCs; j++)
            {
                if (list->dc[j].dcProcessID != 0 && list->dc[j].lastTimeHeardFrom != 0)
                {
                    // replace empty with non empty
                    list->dc[i].dcProcessID = list->dc[j].dcProcessID;
                    list->dc[i].lastTimeHeardFrom = list->dc[j].lastTimeHeardFrom;

                    list->dc[j].dcProcessID = 0;
                    list->dc[j].lastTimeHeardFrom = 0;
                    break;
                }
            }
        }
    }
}
