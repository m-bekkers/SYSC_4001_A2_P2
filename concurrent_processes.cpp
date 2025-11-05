#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main() {

	pid_t pid1,pid2;
	
	pid1 =fork();
	
	if(pid1<0){
		//error
		perror("fork failed");
		return 1;
		
	}
	
	if(pid1==0){
		// child process
		int counter=0;
		while(1){
		
			printf("Process 1 (PID %d): counter = %d \n",getpid(),counter++);
			sleep(1);
								
		}
	}
	
	else{
		// parent process
		pid2 =fork();
		
		if(pid2<0){
			//error
			perror("fork failed");
			return 1;
			
		}
			
		if(pid2==0){
			// child process
			int counter=0;
			while(1){
			
				printf("Process 2 (PID %d): counter = %d \n",getpid(),counter++);
				sleep(1);
									
			}
		}
			
		
		else{
			printf("Parent PID: %d, Child 1 PID: %d, Child 2 PID: %d\n",getpid(), pid1, pid2);
			return 0; // parrent exits.
					
		}	
	}
		
	return 0;
	
}
		
	
