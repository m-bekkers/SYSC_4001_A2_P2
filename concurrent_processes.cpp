#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main() {

	pid_t pid;
	pid =fork();
	
	if(pid<0){
		//error
		perror("fork failed");
		return 1;
		
		}
	if(pid==0){
		// child process
		int counter=0;
		while(1){
		
			printf("Child (PID %d): counter = %d \n",getpid(),counter++);
			sleep(1);
								
			}
		}
		
	else{
		// parent process
		int counter=0;
		while(1){
		
			printf("Parent (PID %d): counter = %d \n",getpid(),counter++);
			sleep(1);
								
			}
		}
	return 0;
	
	}
		
	
