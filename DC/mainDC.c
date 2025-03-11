#include "../Common/common.h"
#include "../Common/logWriter.h"


int main(void)
{
  key_t shmKey;
  shmKey = ftok(".", 16535);

  printf("Key in Data Creator: %d\n", shmKey);
  test();

  int sentinel = 0;
  while (sentinel != 5)
  {
    printf("Writing #%d\n", sentinel);
    writeToFileWithSemaphore("Log message!", DC_PATH);
    sentinel++;
  }

}