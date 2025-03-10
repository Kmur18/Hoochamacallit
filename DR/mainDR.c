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
    key_t shmKey;
    shmKey = ftok(".", 16535);

    printf("Key in Data Reader: %d\n", shmKey);

}