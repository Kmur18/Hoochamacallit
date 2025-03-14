//
// Created by kmurawsky0383 on 10/03/25.
//

#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdbool.h>
#include <time.h>

// #pragma warning(disable: 4996) // This is windows only...

// Function prototypes
int generateRandomNumber(int min, int max);
int checkEventTime(struct tm* event_time_tm);

#define MAX_DC_ROLES 10

#define MSG_MIN 1 // Skip the 0 message when generating random messages
#define MSG_MAX 5 // Change back to 6


// DCInfo struct
typedef struct
{
    pid_t dcProcessID;
    struct tm* lastTimeHeardFrom;
    //struct tm lastTimeHeardFrom;
} DCInfo;

// MasterList struct
typedef struct
{
    int msgQueueID;
    int numberOfDCs;
    DCInfo dc[MAX_DC_ROLES];
} MasterList;

// Messages Enum (0 to 6)
typedef enum
{
    MSG_OKAY = 0,
    MSG_HYDRAULIC_PRESSURE_FAILURE = 1,
    MSG_SAFETY_BUTTON_FAILURE = 2,
    MSG_NO_RAW_MATERIAL = 3,
    MSG_TEMPERATURE_OUT_OF_RANGE = 4,
    MSG_OPERATOR_ERROR = 5,
    MSG_MACHINE_OFFLINE = 6,
} MessageType;

// Message Strings to be used when sending/logging messages
const char *MessageStrings[] = {
    "Everything is OKAY",                 // MSG_OKAY
    "Hydraulic Pressure Failure",         // MSG_HYDRAULIC_PRESSURE_FAILURE
    "Safety Button Failure",              // MSG_SAFETY_BUTTON_FAILURE
    "No Raw Material in the Process",     // MSG_NO_RAW_MATERIAL
    "Operating Temperature Out of Range", // MSG_TEMPERATURE_OUT_OF_RANGE
    "Operator Error",                     // MSG_OPERATOR_ERROR
    "Machine is Off-line"                 // MSG_MACHINE_OFFLINE
};

typedef struct
{
    // Linux/Unix needs this
    long msgType;
    int messagePid;
    int messageType;
} Message;

#endif // COMMON_H
