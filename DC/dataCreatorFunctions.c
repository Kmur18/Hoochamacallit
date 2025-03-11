#include "../Common/common.h"
#include "../Common/logWriter.h"

/*
This application will send a message (via a message queue) to the Data Reader application (the server
component of the solution).
1. Make sure that your DC program follow best practices and checks for the existence of the message
queue before sending its first message
2. If the message queue doesn’t exist, then the DC application will enter a loop in which it will sleep for 10
seconds and try again to see if the message queue has been established and created. The DC continues
this sleep and check protocol until the queue exists
3. Only after the message queue has been created can the DC application enter its main processing loop
4. Once the existence of the queue has been established, the first message that must be sent is an
Everything is OKAY type message
•
Each message must contain the machine’s ID value (use the PID of the process)
•
Each message must contain a randomly selected status (you’ll need to read up on how the rand() function
works) value (except for the 1st message) from the list below
1. 0 : means Everything is OKAY
2. 1 : means Hydraulic Pressure Failure
3. 2 : means Safety Button Failure
4. 3 : means No Raw Material in the Process
5. 4 : means Operating Temperature Out of Range
6. 5 : means Operator Error
7. 6 : means Machine is Off-line
•
The DC will send such a message on a random time basis – between 10 and 30 seconds apart
•
In making the status value of the message random as well as the frequency of the message itself, this
application’s output is not predictable
1. please note that the DC should not expect a response or reply message – all this application needs to
do send message after message
•
It is expected that each DC application logs its activity to a common logging file – see the Application Logging
section at the end of this document
•
When the DC randomly selects the Machine is Off-line status and sends the message, the application
may exit
1. until the Machine is Off-line message is randomly generated and sent, the DC continues to send message
after message

*/

// Put all functions related to the Data Creator here and call them from the dataCreatorMainLoop()

// Where the main loop will occur
void dataCreatorMainLoop()
{
    // Step 1: Check if message queue exists (use a common function?)
    // If the message queue does NOT exist, enter a loop that waits for 10 seconds and checks again

    /*
    // Check if the message queue exists
    // Make this section its own function?...
    while(!checkMessageQueue())
    {
        sleep(QUEUE_CHECK_TIMER);
    }
    */

    // The message queue exists, send the first message (everything is ok)
    // sendMessage(OK_MESSAGE); // Example, look into message information

    // Test code DELETE
    int sentinel = 0;
    while (sentinel != 50)
    {
        printf("Writing #%d\n", sentinel);
        writeToFileWithSemaphore("Log message!", DC_LOG);
        sentinel++;
        sleep(1);
    }
}
