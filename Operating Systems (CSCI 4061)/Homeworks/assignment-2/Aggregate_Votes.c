/*
  login: starx013, nusse007
  date: 03/08/18
  name: Gregory Star, Malik Nusseibeh
  id: 5191430, 4978826
*/

#define _BSD_SOURCE

#include "util.h"
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <stdlib.h>
#include <dirent.h>
#include <stdbool.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

typedef struct candidate {
  char* name;
  int votes;
  struct candidate* next;
} candidate;

candidate* headNode = NULL;

//If a candidate isn't already in the list, add it
void addNewCandidate(char* newName, int votes) {
  candidate* current = headNode;
  while(current->next != NULL){
    current = (current->next);
  }
  current->next = malloc(sizeof(candidate));
  current->next->name = newName;
  current->next->votes = votes;
  current->next->next = NULL;
}

//Increment the candidate with the given name
bool incrementCandidate(char* candidateName) {
  candidate* current = headNode;
  while(current != NULL) {
    current = (current->next);
    if(current != NULL && strcmp(current->name, candidateName) == 0) {
      break;
    }
  }
  if(current == NULL) {
    return false;
  } else {
    current->votes += 1;
    return true;
  }
}

//Combines incrementCandidate and addNewCandidate
//Now only one function needs to be called
//Not super efficient because it redoes the loop but whatever
void processCandidate(char* candidateName, int votes) {
  candidate* current = headNode;
  while(current != NULL){
    current = (current->next);
    if(current != NULL && strcmp(current->name, candidateName) == 0) {
      break;
    }
  }
  if(current == NULL) {
    addNewCandidate(candidateName, votes);
  } else {
    current->votes += votes;
  }
}

void parseChildOutput(char* path) {
  //Open the file and read it into buffer
  char** directory;
  int size = makeargv(path, "/", &directory);
  char filename[255];
  sprintf(filename, "%s/%s.txt", path, directory[size-1]);
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
    processCandidate(name, votes);
  }
}

void create_output(char* path, bool isHighestLevel) {
  char** directories;
  int size = makeargv(path, "/", &directories);
  char* filename = directories[size-1];
  if (isHighestLevel) {
    char** directory;
    char cwd[1024];
    getcwd(cwd, sizeof(cwd));
    int size = makeargv(cwd, "/", &directory);
    filename = directory[size-1];
  }


  strcat(filename, ".txt");
  char* pathname = malloc(sizeof(char)*255);
  sprintf(pathname, "%s/%s", path, filename);
  FILE* file = fopen(pathname, "w");

  printf("%s\n", pathname);
  candidate* current = headNode->next;
  while(current != NULL){
    fprintf(file, "%s:%d", current->name, current->votes);
    if (current->next != NULL)
      fprintf(file, ",");
    else
      fprintf(file, "\n");
    current = (current->next);
  }

  fclose(file);
  chmod(pathname, 0700);
}

void traverseDirectory(char* path){
  DIR* dir;
  if (!(dir = opendir(path))) {
    perror("opendir() error");
    exit(1);
  }
  //Skip "." and ".."
	struct dirent* entry = readdir(dir);
	entry = readdir(dir);

  //First we need to figure out if this directory is a leaf
  bool isLeaf = true;
  while (entry = readdir(dir)) {
		if(entry->d_type == DT_DIR){
      isLeaf = false;
      break;
		}
	}
  //If it's a leaf, then we need to call leafcounter.
  if (isLeaf) {
    if (execl("./Leaf_Counter", "Leaf_Counter", path, (char*)NULL) != 0) {
    	perror("execl() error");
      exit(1);
    }
  } else {
    //A subdirectory was found, so we need to call aggregate_votes on each
    //subdirectory.
    dir = opendir(path);
    //Skip ". and .."
    entry = readdir(dir);
    entry = readdir(dir);
    while (entry = readdir(dir)) {
      char newPath[1000] = "";
      strcpy(newPath, path);
      strcat(newPath, "/");
      strcat(newPath, entry->d_name);
      if(entry->d_type == DT_DIR){
        //First we need to fork so that the parent can keep searching
        //The current directory

        int pipefd[2];
        pipe(pipefd);
        close(pipefd[0]);

        pid_t pid = fork();
        //The child should call aggregate_votes on the subdirectory
        if(pid == 0){
          //Call aggregate_votes on the child
          dup2(pipefd[1], 1);
          if (execl("./Aggregate_Votes", "Aggregate_Votes", newPath, (char*)NULL) != 0) {
          	perror("execl() error");
            exit(1);
          }
        } else {
          //The parent should wait for the child to finish
          //We weren't told how large the tree can be so this
          //avoids fork bombs.
          wait(NULL);
          //Once the child is done, it should have created an output file.
          //We need to scan the output of that child into our data structure
          //then take the results and put them in a file
          parseChildOutput(newPath);
        }
      }
    }
  }
}

void print_list(){
  candidate* current = headNode->next;
  while(current != NULL) {
    current = current->next;
  }
}

int main(int argc, char** argv) {
  if (argc < 2) {
    perror("Incorrect number of arguments\n");
  } else {
  	headNode = malloc(sizeof(candidate));
    if (strcmp(argv[1], ".") == 0) {
      traverseDirectory(argv[1]);
      create_output(argv[1], true);
    } else {
      traverseDirectory(argv[1]);
      create_output(argv[1], false);
    }
  }

  return 0;
}
