#include <iostream>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string>
#include <chrono>
#include <thread>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#include "part2-4_shared.hpp"

int main () {
    int pid_num = getpid();

    struct shared_vars *shared_data; // shared struct
    void *shared_memory = (void *)0; // void ptr for use by shmat

    int shmid; // stores the id of the shared memory
    shmid = shmget((key_t) 6969, sizeof(struct shared_vars), 0666 | IPC_CREAT); // create a shared memory segment with key 6969

    // check for shmid failure
    if (shmid == -1) {
        std::cout << "Error while getting shared memory, exiting...";
        exit(EXIT_FAILURE);
    }

    shared_memory = shmat(shmid, (void *)0, 0); // make the shared mem accessible to program

    // check for shmat failure
    if (shared_memory == (void *)-1) {
        std::cout << "Error while using shmat, exiting...";
        exit(EXIT_FAILURE);
    }

    /* now that shared memory contains the first addess of the allocated mem, 
    cast it to a shared_vars struct so it has the 2 vars we want */
    shared_data = (struct shared_vars *)shared_memory; 

    while(shared_data->shared_counter <= 500) {
        
        if (shared_data->shared_counter >= 100) {
            shared_data->shared_counter++;

            std::cout << "Child" << " process PID(" << pid_num << ") cycle number: " << shared_data->shared_counter;

            if (shared_data->shared_counter % 3 == 0) {
                std::cout << " -- " << shared_data->shared_counter << " is divisible by 3";
            }

            std::cout << std::endl;

            std::this_thread::sleep_for(std::chrono::milliseconds(50));
        }
    }

    exit(0);
    return 0;
}