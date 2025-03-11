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
// #pragma warning(disable: 4996) // This is windows only...

#define MAX_DC_ROLES 10

typedef struct
{
    pid_t dcProcessID;
    int lastTimeHeardFrom;
} DCInfo;

typedef struct
{
    int msgQueueID;
    int numberOfDCs;
    DCInfo dc[MAX_DC_ROLES];
} MasterList;


#endif // COMMON_H
