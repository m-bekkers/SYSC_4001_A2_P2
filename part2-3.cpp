#include <iostream>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string>
#include <chrono>
#include <thread>

int main() {
    pid_t pid;
    pid = fork();

    int counter = 0;
    std::string message = "";

    // check fork went OK
    switch (pid) {
    case -1:
        std::cout << "Error: Fork Failed" << std::endl;
        exit(1);
        break;
    case 0:
        std::cout << "Process is child, proceeding..." << std::endl;
        message = "Child";
        execl("./bin/part2-3_process2", "part2-3_process2", NULL);
        break;
    
    default:
        std::cout << "Process is parent, proceeding..." << std::endl;
        message = "Parent";
    }

    int pid_num = getpid();

    std::cout << message << " process PID(" << pid_num << ") cycle number: " << counter << std::endl;
    
        while (1) {
            int stat_val;
            pid_t child_pid;
            child_pid = wait(&stat_val);
            printf("Child has finished: PID = %d\n", child_pid);
            
            if (WIFEXITED(stat_val)) {
                printf("Child exited with code %d\n", WEXITSTATUS(stat_val));
            }
            else {
                printf("Child terminated abnormally\n");
            }
            std::cout << "Child process has terminated, terminating parent process..." << std::endl;
            exit(0);

        }

        std::cout << message << " process PID(" << pid_num << ") cycle number: " << counter << std::endl;
        
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }