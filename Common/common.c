#include "common.h"

int generateRandomNumber(int min, int max) {
    // Ensure the random number generator is seeded only once
    static int seeded = 0;
    if (!seeded) {
        srand(time(NULL));  // Seed the random number generator with the current time
        seeded = 1;
    }

    // Generate a random number between min and max inclusive
    return rand() % (max - min + 1) + min;
}

int checkEventTime(struct tm* event_time_tm)
{
    // Get current time
    time_t now = time(NULL); // Current time in seconds since epoch
    struct tm *current_time_tm = localtime(&now); // Convert to local time

    // Print current time for debugging
    printf("Current time: %02d:%02d:%02d\n", current_time_tm->tm_hour, current_time_tm->tm_min, current_time_tm->tm_sec);

    // Convert the input event_time_tm (struct tm) to time_t
    time_t event_time = mktime(event_time_tm); // Convert struct tm to time_t

    // Check if mktime() failed (in case the input struct tm is invalid)
    if (event_time == -1) {
        printf("Error converting struct tm to time_t\n");
        return -1; // Invalid time
    }

    // Calculate the difference in time (in seconds)
    printf("Time now = %ld\n", now);
    printf("EventTime = %ld\n", event_time);
    double timeDifference = difftime(now, event_time);
    printf("Time Diff: %lf seconds\n", timeDifference);

    // Check if event occurred within 35 seconds
    if (timeDifference <= 10) {
        printf("Event occurred within 10 seconds.\n");
        return 1; // Event happened within 35 seconds
    } else {
        printf("Event occurred after more than 10 seconds.\n");
        return 0; // Event did not happen within 35 seconds
    }
}