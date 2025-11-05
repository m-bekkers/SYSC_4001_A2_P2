/**
Laavanya Nayar, 101157871

**/

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>

int main() {
	int counter=0;
	int cycle =0;
		
	while(1){
		printf("Process 2 (PID %d) Cycle number: %d", getpid(), cycle);
			
		if(counter % 3 == 0){
			printf("---%d is a multiple of 3", counter);
		
		}
		printf("\n");
		
		counter--;
		cycle++;
		sleep(1);
								
		}
	return 0; 

}
