#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char** argv) {

	if (argc < 2) {

		printf("Incorrect number of args: given %d, expected 1.\n", argc - 1);
		exit(1);
	}

	
	pid_t pid1 = fork();
	pid_t pid2;
	if(pid1 == 0){
		//execl
		execl("rtime.o", argv[0], argv[1], NULL);
	} else {
		//wait
		int* status = malloc(sizeof(int));
		wait(status);
		pid2 = fork();
		if(pid2 == 0){
			//execv
			execv("rtime.o", argv);
		} else {
			//wait
			wait(status);
			//exit
			exit(0);
		}
	}

	
	
	
	// TODO: Fill in your code here.

}
