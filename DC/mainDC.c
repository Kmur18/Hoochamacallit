#include "../Common/common.c"
// #include "../Common/logWriter.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#include "dataCreatorFunctions.h"

int main(void)
{
  key_t shmKey;
  shmKey = ftok(".", 16535);

  printf("Key in Data Creator: %d\n", shmKey);

  key_t messageKey;
  int messageQueueId; // message queue ID

  // Create MessageKey
  messageKey = ftok("../", 'M');
  if (messageKey == -1)
  {
    printf("(CLIENT) Cannot create key!\n");
    fflush(stdout);
    return 0;
  }

  // Check for MessageQueue
  messageQueueId = msgget(messageKey, 0);
  while (messageQueueId == -1)
  {
    messageQueueId = msgget(messageKey, 0);
    // Queue doesnt exist
    printf("Message queue not found!\n");
    sleep(10);
    // Loop back until queue exists
  }

  printf("Message queue found!\n");

  // int retCode;
  //
  // Send message (0) for all okay after we get msgque, before main loop
  Message msg;
  msg.messagePid = (int) getpid();
  msg.messageType = generateRandomNumber(MSG_MIN, MSG_MAX);
  msg.msgType = 1;

  int returnCode = msgsnd(messageQueueId, (void*)&msg, sizeof(Message) - sizeof(long), 0);


  if (returnCode == -1)
  {
    printf("Error sending message!\n");
    perror("Error sending message");
    return -15;
  }

  printf("Message sent!\n");

  //
  while (true)
  {
    printf("In main loop sleeping 15\n");
    sleep(15);
    // SendMessage() to queue function
    // Check return from SendMessage() function?
    // maybe use return code to know what to LOG
    // If return code tells that hte message sent was (7) exit message
    // Break while loop
    break;
  }

  //dataCreatorMainLoop();

  return 0;
}