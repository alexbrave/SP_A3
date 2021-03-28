/*
 *  FILE          : checkIDinMasterList.c
 *  PROJECT       : SENG2030-21W-Sec1-System Programming - Assignment #3
 *  PROGRAMMER    : Andrey Takhtamirov, Alex Braverman
 *  FIRST VERSION : March 26, 2020 
 *  DESCRIPTION   : 
 *			This file contains the function which checks for a given clientID
 *              in a given MasterList, returning the found index (if any).
*/
#include "../inc/DR.h"

/*
* FUNCTION 		: removeClient
* DESCRIPTION 	: Check if ID is in MasterList, returning the index if contained
* PARAMETERS 	: MasterList *list
                    : pointer to MasterList which contains the DCs
                  int clientID
                    : ID of the client to locate
* RETURNS 		: int : the index of the client (if none, -1)
*/
int checkIDinMasterList(MasterList list, int clientID)
{
    int listCounter = 0;

    // scan list for ID
    while (listCounter < list.numberOfDCs)
    {
        if (list.dc[listCounter].dcProcessID == clientID)
        {
            // exists in list, return index
            return listCounter;
        }
        listCounter++;
    }

    return NOT_FOUND;
}
