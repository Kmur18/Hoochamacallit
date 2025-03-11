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
  // key_t shmKey;
  // shmKey = ftok(".", 16535);

  // printf("Key in Data Creator: %d\n", shmKey);
  //
  // key_t message_key;
  // int msgQID; // message queue ID
  //
  // // Create MessageKey
  // message_key = ftok("../", 'M');
  // if (message_key == -1)
  // {
  //   printf("(CLIENT) Cannot create key!\n");
  //   fflush(stdout);
  //   return 0;
  // }
  //
  // // Check for MessageQueue
  // msgQID = msgget(message_key, 0);
  // while (msgQID == -1)
  // {
  //   msgQID = msgget(message_key, 0);
  //   // Queue doesnt exist
  //   printf("Message queue not found!\n");
  //   sleep(10);
  //   // Loop back until queue exists
  // }
  //
  // printf("Message queue found!\n");
  //
  // int retCode;
  // //
  // // Send message (0) for all okay after we get msgque, before main loop
  // Message msg;
  // msg.messagePid = (int) getpid();
  // msg.messageType = MSG_OKAY;
  // msg.msgType = 1;

  // retCode = msgsnd(msgQID, (void*)&msg, sizeof(Message) - sizeof(long), 0);

  int messageType = generateRandomNumber(MSG_MIN, MSG_MAX);

  printf("Message type: %s\n", MessageStrings[messageType]);
  // if (retCode == -1)
  // {
  //   printf("Error sending message!\n");
  //   perror("Error sending message");
  //   return -15;
  // }
  //
  // printf("Message sent!\n");
  //
  // //
  // while (true)
  // {
  //   printf("In main loop sleeping 15\n");
  //   sleep(15);
  //   // SendMessage() to queue function
  //   // Check return from SendMessage() function?
  //   // maybe use return code to know what to LOG
  //   // If return code tells that hte message sent was (7) exit message
  //   // Break while loop
  //   break;
  // }

  //dataCreatorMainLoop();

  return 0;
}