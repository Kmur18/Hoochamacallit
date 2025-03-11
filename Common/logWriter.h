
#ifndef TEST_H
#define TEST_H

#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <fcntl.h>
#include <unistd.h>

// Defines to write to specific log files
#define DC_PATH "DClog.txt"
// production log: /tmp/dataCreator.log

#define DR_PATH "DRlog.txt"
// production log: /tmp/dataMonitor.log

#define DX_PATH "DXlog.txt"
// production log: /tmp/dataCorruptor.log

// Used in a switch to determine which type of log will be written
#define DC_LOG 0
#define DR_LOG 1
#define DX_LOG 2

// Semaphore defines
#define SEM_KEY_PATH "." // Used with ftok()
#define SEM_ID 16535        // Arbitrary project ID for ftok()

void writeToFileWithSemaphore(char *stringToWrite, int logType);

#endif // TEST
