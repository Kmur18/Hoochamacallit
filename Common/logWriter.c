#include "logWriter.h"
#include "common.h"

void test()
{
    printf("Testing from functions!\n\n");
    printf("\t\tWowoeeee!\n");
}

void lock_semaphore(int semaphoreId)
{
    struct sembuf sem_lock = {0, -1, SEM_UNDO}; // P operation (wait)
    semop(semaphoreId, &sem_lock, 1);
}

void unlock_semaphore(int semaphoreId)
{
    struct sembuf sem_unlock = {0, 1, SEM_UNDO}; // V operation (signal)
    semop(semaphoreId, &sem_unlock, 1);
}

// The path is used by the caller (#define in fileWriter.h)
/*

Call with :
DC_PATH
DR_PATH
DX_PATH
To write to their respective file paths

*/
void writeToFileWithSemaphore(char *stringToWrite, char* file_path)
{
    // Generate a key for the semaphore
    key_t key = ftok(SEM_KEY_PATH, SEM_ID);
    if (key == -1)
    {
        perror("ftok failed"); // Print the errno
        exit(EXIT_FAILURE);
    }

    // Get or create a semaphore
    int semid = semget(key, 1, IPC_CREAT | 0666);
    if (semid == -1)
    {
        perror("semget failed"); // Print the errno
        exit(EXIT_FAILURE);
    }

    // Initialize semaphore to 1
    semctl(semid, 0, SETVAL, 1);

    // Lock semaphore before writing
    lock_semaphore(semid);


    FILE *file = fopen(file_path, "a");
    if (file == NULL)
    {
        perror("Error opening file"); // Print the errno
        unlock_semaphore(semid);
        exit(EXIT_FAILURE);
    }

    // This is where the writing occurs WITH the semaphore
    fprintf(file, "String: \"%s\" - From PID: %d\n", stringToWrite, getpid());
    fclose(file);

    // Unlock semaphore, writing is complete
    unlock_semaphore(semid);
}
