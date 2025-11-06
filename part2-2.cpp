#include <iostream>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <string>

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
        break;
    
    default:
        std::cout << "Process is parent, proceeding..." << std::endl;
        message = "Parent";
    }

    int pid_num = getpid();

    std::cout << message << " process PID(" << pid_num << ") cycle number: " << counter << std::endl;
    
    while (1) {
    
        if (pid == 0) {
            counter--;
        }
        else {
            counter++;
        }

        std::cout << message << " process PID(" << pid_num << ") cycle number: " << counter;

        if (counter % 3 == 0) {
            std::cout << " -- " << counter << " is divisible by 3";
        }

        std::cout << std::endl;
        
        sleep(1);
    }
}