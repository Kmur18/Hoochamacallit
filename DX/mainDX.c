// #include "../Common/logWriter.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#include "../Common/common.c"

// Define the choice options
#define DO_NOTHING_00 0
#define KILL_DC_01_01 1
#define KILL_DC_03_02 2
#define KILL_DC_02_03 3
#define KILL_DC_01_04 4
#define KILL_DC_03_05 5
#define KILL_DC_02_06 6
#define KILL_DC_04_07 7
#define DO_NOTHING_08 8
#define KILL_DC_05_09 9
#define DELETE_QUEUE_10 10
#define KILL_DC_01_11 11
#define KILL_DC_06_12 12
#define KILL_DC_02_13 13
#define KILL_DC_07_14 14
#define KILL_DC_03_15 15
#define KILL_DC_08_16 16
#define DELETE_QUEUE_17 17
#define KILL_DC_09_18 18
#define DO_NOTHING_19 19
#define KILL_DC_10_20 20

int main (int argc, const char * argv[])
{
  key_t message_key;
  int msgQID; // message queue ID

  message_key = ftok("../", 'M');
  if (message_key == -1)
  {
    printf("(EVIL) error creating key!\n");
    fflush(stdout);
    return -5;
  }

  //Requirments say to have this logic for the smhkey for shared mem for mastyerlist
  //Not for msgque but msgQID will be needed to delete the queue is some destruction
  //casses, the check if exists and sleep may not be needed for msgQID getting.
  msgQID = msgget(message_key, 0);
  while (msgQID == -1)
  {
    msgQID = msgget(message_key, 0);
    // Queue doesnt exist
    printf("Message queue not found!\n");
    sleep(10);
    // Loop back until queue exists
  }




  //WHEEL OF megaDEATH
  choice = generateRandomNumber(DO_NOTHING_00, KILL_DC_10_20);

  switch(choice){
    case DO_NOTHING_00:
      break;

    case KILL_DC_01_01:
      break;

    case KILL_DC_03_02:
      break;

    case KILL_DC_02_03:
      break;

    case KILL_DC_01_04:
      break;

    case KILL_DC_03_05:
      break;

    case KILL_DC_02_06:
      break;

    case KILL_DC_04_07:
      break;

    case DO_NOTHING_08:
      break;

    case KILL_DC_05_09:
      break;

    case DELETE_QUEUE_10:
      msgctl(msgQID, IPC_RMID, NULL);
      break;

    case KILL_DC_01_11:
      break;

    case KILL_DC_06_12:
      break;

    case KILL_DC_02_13:
      break;

    case KILL_DC_07_14:
      break;

    case KILL_DC_03_15:
      break;

    case KILL_DC_08_16:
      break;

    case DELETE_QUEUE_17:
      msgctl(msgQID, IPC_RMID, NULL);
      break;

    case KILL_DC_09_18:
      break;

    case DO_NOTHING_19:
      break;

    case KILL_DC_10_20:
      break;

    default:
      break;
  }

    return 0;
}