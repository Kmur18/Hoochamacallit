// #include "../Common/common.h"
// #include "../Common/logWriter.h"

#include "dataCreatorFunctions.h"

int main(void)
{
  // key_t shmKey;
  // shmKey = ftok(".", 16535);

  // printf("Key in Data Creator: %d\n", shmKey);

  dataCreatorMainLoop();

  return 0;

}