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
#include <sys/sem.h>

#include "part2-5_shared.hpp"

static int set_semvalue(void);
static void del_semvalue(void);
static int semaphore_p(void);
static int semaphore_v(void);

static int sem_id;

static int set_semvalue(void) {
    union semun sem_union;

    sem_union.val = 1;
    if (semctl(sem_id, 0, SETVAL, sem_union) == -1) return(0);
    return (1);
}

static void del_semvalue(void) {
    union semun sem_union;

    if (semctl(sem_id, 0, IPC_RMID, sem_union) == -1)
    fprintf(stderr, "Failed to delete semaphore\n");
}

static int semaphore_p(void) {
    struct sembuf sem_b;

    sem_b.sem_num = 0;
    sem_b.sem_op = -1; // P()
    sem_b.sem_flg = SEM_UNDO;
    if (semop(sem_id, &sem_b, 1) == -1) {
        fprintf(stderr, "semaphore_p failed\n");
        return(0);
    }
    return 1;
}

static int semaphore_v(void) {
    struct sembuf sem_b;

    sem_b.sem_num = 0;
    sem_b.sem_op = 1; // V()
    sem_b.sem_flg = SEM_UNDO;
    if (semop(sem_id, &sem_b, 1) == -1) {
        fprintf(stderr,"semaphore_v failed\n");
        return(0);
    }
    return 1;
}

int main() {
    // create pid
    pid_t pid;
    pid = fork();

    struct shared_vars *shared_data; // shared struct
    void *shared_memory = (void *)0; // void ptr for use by shmat
    std::string message = ""; // to distinguish parent from child

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

    std::cout << "Memory attached at " << shared_memory << "." << std::endl;

    shared_data = (struct shared_vars *)shared_memory; // now that shared memory contains the first addess of the allocated mem,
                                                       // cast it to a shared_vars struct so it has the 2 vars we want

    shared_data->multiple = 3; // chose any value really
    shared_data->shared_counter = 0;

    // check fork went OK
    switch (pid) {
    case -1:
        std::cout << "Error: Fork Failed" << std::endl;
        exit(1);
        break;
    case 0:
        std::cout << "Process is child, proceeding..." << std::endl;
        message = "Child";
        execl("./bin/part2-5_process2", "part2-5_process2", NULL);
        break;
    
    default:
        std::cout << "Process is parent, proceeding..." << std::endl;
        message = "Parent";
    }

    int pid_num = getpid();

    //std::cout << message << " process PID(" << pid_num << ") cycle number: " << shared_data->shared_counter << std::endl;

    sem_id = semget((key_t)6969, 1, 0666 | IPC_CREAT);

    if (!set_semvalue()) { // error while getting sem_id
        std::cout << "Error while initializing semaphore" << std::endl;
        exit(EXIT_FAILURE);
    }


    
    while (shared_data->shared_counter <= 500) {
        //int stat_val;
        //pid_t child_pid;
        //child_pid = wait(&stat_val);
        //printf("Child has finished: PID = %d\n", child_pid);
        
        //if (WIFEXITED(stat_val)) {
        //    printf("Child exited with code %d\n", WEXITSTATUS(stat_val));

        //}
        //else {
        //    printf("Child terminated abnormally\n");

        //}

        //std::cout << "Child process has terminated, terminating parent process..." << std::endl;
        //exit(0);

        semaphore_p();

        std::cout << message << " process PID(" << pid_num << ") cycle number: " << shared_data->shared_counter;

        if (shared_data->shared_counter % 3 == 0) {
            std::cout << " -- " << shared_data->shared_counter << " is divisible by 3";
        }

        shared_data->shared_counter++;

        std::cout << std::endl;

        semaphore_v();
        
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }

    shmdt(shared_memory);
    shmctl(shmid, IPC_RMID, 0);
    del_semvalue();
}