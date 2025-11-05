/**
Laavanya Nayar, 101157871

**/


#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>

int main() {

	pid_t pid;
	pid =fork();
	
	if(pid<0){
		//error
		perror("fork failed");
		exit(1);
		
		}
	if(pid==0){
		// child process to replace with process 2
		execl("./bin/process2","process2",NULL);
		perror("exec failed");
		
		}
		
	else{
		// parent process so count upwards
		int counter=0;
		int cycle =0;
		
		while(1){
			printf("Process 1 (PID %d) Cycle number: %d", getpid(), cycle);
			
			if(counter % 3 == 0){
				printf("---%d is a multiple of 3", counter);
			
			}
			printf("\n");
		
			counter++;
			cycle++;
			sleep(1);
								
			}
		}
	return 0;
	
	}
		
	
