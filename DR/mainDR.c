//
// Created by kmurawsky0383 on 10/03/25.
//

#include "../Common/common.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>


int main(void) {
    //key_t shmKey;
    //shmKey = ftok(".", 16535);

    //printf("Key in Data Reader: %d\n", shmKey);
    //printf("Volfer testing shit\n");

    int msgQID;
    key_t message_key;

    message_key = ftok ("..", 'M');
  if (message_key == -1)
  {
    printf ("(SERVER) Cannot create key!\n");
    fflush (stdout);
    return 1;
  }


  //Checking if msgqueue exists, not creating yet
  msgQID = msgget(message_key, 0660);
  if (msgQID == -1)
  {
    //Could add errno check to see if the -1 is from lack of queue or a different error
    printf ("(SERVER) queue does not exist\n");
    fflush (stdout);
    // create the message queue
  	msgQID = msgget (message_key, IPC_CREAT | 0660);
    sleep(15);//Sleep after creating queue
  }
  //msgctl(msgQID, IPC_RMID, NULL);
    printf("Queue created sleeping 10\n");
    sleep(10);

  Message msg;
  msgrcv(msgQID, &msg, sizeof(Message) - sizeof(long), 1, 0);

  printf("Message received: %d | %d \n", msg.messagePid, msg.messageType);

    msgctl(msgQID, IPC_RMID, NULL);
    printf("Queue removed\n");
    return 0;
}