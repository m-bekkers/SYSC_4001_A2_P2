#include <iostream>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <string>

int main () {
    int counter = 0;
    int pid_num = getpid();

    while(1) {
        
        counter--;

        std::cout << "Child" << " process PID(" << pid_num << ") cycle number: " << counter;

        if (counter % 3 == 0) {
                std::cout << " -- " << counter << " is divisible by 3";
            }

            std::cout << std::endl;

            sleep(1);
    }
}