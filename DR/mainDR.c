//
// Created by kmurawsky0383 on 10/03/25.
//

#include "../Common/common.c"


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
  // *********************** GET RID ONCE READY - THIS IS FOR MANUALLY DESTROYING THE MSGQUEUE IF THE PROGRAM FAILS TO REACH THE END
//msgctl(msgQID, IPC_RMID, NULL);
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

//Loop for receiving messages from DCs
while (masterList.numberOfDCs > 0 && masterList.numberOfDCs <= MAX_DC_ROLES)
{
  retCode = msgrcv(msgQID, &msg, sizeof(Message) - sizeof(long), 1, 0);

  if (retCode == -1)
  {
    printf ("(SERVER) Error receiving message!\n");
    perror("Error receiving message");
    return -16;
  }

  printf("Message received: %d | %d \n", msg.messagePid, msg.messageType);

  // Check if we have heard from this user in the master list
  if (msg.messageType == MSG_OKAY)
  {
    masterList.dc[masterList.numberOfDCs].dcProcessID = msg.messagePid;
    masterList.dc[masterList.numberOfDCs].lastTimeHeardFrom = localtime(&nowTime);
    masterList.numberOfDCs++;
  }
  else if (msg.messageType == MSG_MACHINE_OFFLINE) // Check if its a 6 msg
  {
    for (int i = 0; i < masterList.numberOfDCs; i++)
    {
      if (masterList.dc[i].dcProcessID == msg.messagePid)
      {
        // check if the client to be removed is the last/max amount in the masterList 10th client 9th index
        if (i == MAX_DC_ROLES - 1)
        {
          masterList.dc[i].dcProcessID = 0;
          masterList.dc[i].lastTimeHeardFrom = NULL;
        }
        else
        {
          // Shift all elements after the found DC to the left
          for (int j = i; j < masterList.numberOfDCs; j++)
          {
            masterList.dc[j] = masterList.dc[j + 1];
          }
        }
        masterList.numberOfDCs--;
        break; // Exit the loop after removing the DC
      }
    }
  }
  else // We got a msg from 1-5 update its pid's time heard from
  {
    // Add msg time to master list
    for (int i = 0; i < masterList.numberOfDCs; i++)
    {
      // check for dc pid's
      if (masterList.dc[i].dcProcessID == msg.messagePid)
      {
        // We have heard from this pid - Store the time received
        masterList.dc[i].lastTimeHeardFrom = localtime(&nowTime);
      }
    }
  }

  // Variable for return of the time checker
  int heardStatus;
printf("bob\n");
  // Check master list last heard from to cut off all who hasn't been heard from in 35 seconds
  for (int i = 0; i < masterList.numberOfDCs; i++)
  {
    heardStatus = checkEventTime(masterList.dc[i].lastTimeHeardFrom);

    printf("***************return coDE: %d\n", heardStatus);
    if (heardStatus == 0) // client was not heard from within 35 seconds
    {
      printf("Hi I am Pork John\n");
      // check if the client to be removed is the last/max amount in the masterList 10th client 9th index
      if (i == MAX_DC_ROLES - 1)
      {
        masterList.dc[i].dcProcessID = 0;
        masterList.dc[i].lastTimeHeardFrom = NULL;
      }
      else
      {
        // Shift all elements after the found DC to the left
        for (int j = i; j < masterList.numberOfDCs; j++)
        {
          masterList.dc[j] = masterList.dc[j + 1];
        }
        i--; // decrement the i counter so it goes to the next proper DC to check time because we just reordered/removed one
      }
      masterList.numberOfDCs--;
    }
  }


 // end of DR main processing loop
  sleep(1.5);
}

    msgctl(msgQID, IPC_RMID, NULL);
    printf("Queue removed\n");
    return 0;
}