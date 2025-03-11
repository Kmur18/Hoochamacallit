//
// Created by kmurawsky0383 on 10/03/25.
//

#include "../Common/common.h"


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

  printf("Queue created sleeping 10\n");
  sleep(10);

  // Create master list initialized to 0
  MasterList masterList = {0};

  // Message received return code
  int retCode;

  // Create and receive msg from messagequeue
  Message msg;
  retCode = msgrcv(msgQID, &msg, sizeof(Message) - sizeof(long), 1, 0);

  if (retCode == -1)
  {
    printf ("(SERVER) Error receiving message!\n");
    perror("Error receiving message");
    return -16;
  }

  printf("Message received: %d | %d \n", msg.messagePid, msg.messageType);

  // Alter masterList
  masterList.numberOfDCs++;
  masterList.dc[0].dcProcessID = msg.messagePid;
  time_t nowTime = time(NULL);
  masterList.dc[0].lastTimeHeardFrom = localtime(&nowTime);

  char buffer[80];
  strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", masterList.dc[0].lastTimeHeardFrom);
  printf("Local Time: %s\n", buffer);




    msgctl(msgQID, IPC_RMID, NULL);
    printf("Queue removed\n");
    return 0;
}