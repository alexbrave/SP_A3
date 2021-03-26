#include "../inc/DR.h"

// int log(char* message)
// {
//     int status = LOG_SUCCESS;
//     long currDate;
//     long currTime;

//     char dateStr = "date";
//     char timeStr = "time";
//     char *logStr = NULL;

//     FILE *fp = NULL;

//     fp = fopen(LOG_LOCATION, "a");

//     if(fp == NULL)
//     {
//         printf("Error writing to log file!\n");
//         status = LOG_ERROR;
//     }

//     logStr = strcat(dateStr, timeStr);

//     logStr = strcat(logStr, " : ");

//     logStr = strcat(logStr, message);

//     fprintf(fp, "%s", logStr);

//     fclose(fp);

//     return status;
// }
