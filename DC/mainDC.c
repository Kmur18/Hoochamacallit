#include "../Common/common.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>


int main(void) {
  key_t shmKey;
  shmKey = ftok(".", 16535);

  printf("Key in Data Creator: %d\n", shmKey);

}