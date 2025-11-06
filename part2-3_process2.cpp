#include <iostream>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string>
#include <chrono>
#include <thread>

int main () {
    int counter = 0;
    int pid_num = getpid();

    while(counter >= -500) {
        
        counter--;

        std::cout << "Child" << " process PID(" << pid_num << ") cycle number: " << counter;

        if (counter % 3 == 0) {
            std::cout << " -- " << counter << " is divisible by 3";
        }

            std::cout << std::endl;

            std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }

    exit(0);
    return 0;
}