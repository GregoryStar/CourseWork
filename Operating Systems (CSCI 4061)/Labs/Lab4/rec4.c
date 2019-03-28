#define _BSD_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char** argv) {

	if (argc < 2) {

		printf("Wrong number of args, expected 1, given %d", argc - 1);
		exit(1);
	}
	pid_t childpid;
	int fd[2];
	pipe(fd);
	int status;
	fork();
	if(childpid == 0){
		int fileDescript = open("output.txt", O_CREAT | O_RDWR);
		chmod("output.txt", 0700);
		write(fd[1], "output.txt", 11);
		dup2(fileDescript, 1);
		execv("rec3.o", argv);
		
	} else {
		wait(&status);
		close(fd[1]);
		char filename[11];
		read(fd[0], filename, 11);
		chmod("output.txt", 0700);
		int fileFD = open(filename, O_RDONLY);
		int i = 0;
		int currentNum = 0;
		char tempOutput[11];
		read(fileFD, tempOutput, 11);
		while(atoi(tempOutput) > currentNum){
			i++;
			currentNum = atoi(tempOutput);
			read(fileFD, tempOutput, 11);
		}
		
		if(i == 2 * atoi(argv[1])){
			printf("Correct");
		} else {
			printf("Incorrect");
		}
		close(fileFD);
	}
	


	// TODO: Your code goes here.
}
