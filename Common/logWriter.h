
#ifndef TEST_H
#define TEST_H

#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <fcntl.h>
#include <unistd.h>

// Defines to write to specific log files
// #define DC_PATH "./DC/DClog.txt" // How to put it in another specific directory
// I put these in the root to make it easier for now
#define DC_PATH "DClog.txt"
#define DR_PATH "DRlog.txt"
#define DX_PATH "DXlog.txt"

#define SEM_KEY_PATH "."      // Used with ftok()
#define SEM_ID 65             // Arbitrary project ID for ftok()

void writeToFileWithSemaphore(char* stringToWrite, char* file_path);

#endif // TEST
