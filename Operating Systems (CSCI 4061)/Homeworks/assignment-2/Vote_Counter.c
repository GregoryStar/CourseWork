/*
  login: starx013, nusse007
  date: 03/08/18
  name: Gregory Star, Malik Nusseibeh
  id: 5191430, 4978826
*/

#include "util.h"
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>

void find_winner(char* filename) {
	printf("%s\n", filename);
	FILE* file;
	if (!(file = fopen(filename, "r"))) {
		perror("fopen() error");
		exit(1);
	}
	fseek(file, 0, SEEK_END);
  int length = ftell(file);
  fseek(file, 0, SEEK_SET);
  char* buffer = malloc(sizeof(char)*length);
  fread(buffer, 1, length, file);
  fclose(file);

	char* winner = malloc(sizeof(char));
	int highestCount = 0;

   //Break the file into an array of strings by delimiting ','
  char** entries;
  int numEntries = makeargv(buffer, ",", &entries);
  //Populate candidate list
  for(int i = 0; i < numEntries; i++){
  //split the candidate from the count_votes
    char** subEntries;
    int numSubEntries = makeargv(entries[i], ":", &subEntries);
    char* name = subEntries[0];
    int votes = atoi(subEntries[1]);
    if (votes > highestCount) {
    	highestCount = votes;
    	winner = realloc(winner, sizeof(name));
    	strcpy(winner, name);
    }
	}

	file = fopen(filename, "a");
	fprintf(file, "Winner:%s\n", winner);
	fclose(file);
}

int main(int argc, char** argv) {

  char *path, *filename, *pathname;
  char** directory;
  int size;

  if (argc > 1) {
		//The program is executed on the given directory
    path = malloc(255);
    strcpy(path, argv[1]);

		//Split the path name by '/' to find directory structure
    size = makeargv(path, "/", &directory);
  } else {
		//The program should be executed on the cwd
    path = malloc(sizeof(char));
    strcpy(path, ".");
    char cwd[1024];
    if (!getcwd(cwd, sizeof(cwd)))
      perror("getcwd() error");
    else
      size = makeargv(cwd, "/", &directory);
  }
  filename = directory[size-1];
  pathname = malloc(sizeof(char)*255);
  sprintf(pathname, "%s/%s.txt", path, filename);

	int pipefd[2];
	pipe(pipefd);
	close(pipefd[0]);

  pid_t pid = fork();
  if (pid == 0) {
		dup2(pipefd[1], 1);
    if (execl("./Aggregate_Votes", "Aggregate_Votes", path, (char*) NULL) != 0)
      perror("execl() error");
  } else {
    wait(0);
    find_winner(pathname);
  }

  return 0;
}
