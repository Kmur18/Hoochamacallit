
#ifndef TEST_H
#define TEST_H

#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <fcntl.h>
#include <unistd.h>

#define DC_PATH "DClog.txt" // File to write to
#define DR_PATH "DRlog.txt"
#define DX_PATH "DXlog.txt"

#define SEM_KEY_PATH "."      // Used with ftok()
#define SEM_ID 65             // Arbitrary project ID for ftok()

void test();
void writeToFileWithSemaphore(char* stringToWrite, char* file_path);

#endif // TEST
