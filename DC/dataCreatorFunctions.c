#include "../Common/common.h"
#include "../Common/logWriter.h"

void dataCreatorMainLoop()
{
    int sentinel = 0;
    while (sentinel != 5)
    {
        printf("Writing #%d\n", sentinel);
        writeToFileWithSemaphore("Log message!", DC_PATH);
        sentinel++;
    }
}
