/*
  login: starx013, nusse007
  date: 03/08/18
  name: Gregory Star, Malik Nusseibeh
  id: 5191430, 4978826
*/

#include "util.h"
#include <stdio.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

typedef int bool;
#define true 1;
#define false 0;

typedef struct candidate {
  char* name;
  int votes;
  struct candidate* next;
} candidate;

candidate* headNode = NULL;

bool is_leaf(char* path) {
  DIR* dir;
  struct dirent* entry;

  if (!(dir = opendir(path))) {
    perror("opendir() error");
    exit(1);
  }

  while (entry = readdir(dir)) {
    //printf("%s\n", entry->d_name);
    if (!strcmp(entry->d_name, "votes.txt")) {
      return true;
    }
  }

  return false;
}

void addNewCandidate(char* newName){
  candidate* current = headNode;
  while(current->next != NULL){
    current = (current->next);
  }
 current->next = malloc(sizeof(candidate));
 current->next->name = newName;
 current->next->votes = 1;
 current->next->next = NULL;
}

bool incrementCandidate(char* candidateName){
  candidate* current = headNode;
  while(current != NULL){
    current = (current->next);
    if(current != NULL && strcmp(current->name, candidateName) == 0){
      break;
    }
  }
  if(current == NULL){
    return false;
  } else {
    current->votes += 1;
    return true;
  }
}

void count_votes(char* path) {
  headNode = malloc(sizeof(candidate));
  char filename[255];
  sprintf(filename, "%s/votes.txt", path);
  //printf("reading file %s\n", filename);
  FILE* file;
  if (!(file = fopen(filename, "r"))) {
      perror("fopen() error");
      exit(1);
  }
  fseek(file, 0, SEEK_END);
  int length = ftell(file);
  fseek(file, 0, SEEK_SET);
  char* buffer = malloc(sizeof(char)*length+1);
  fread(buffer, 1, length, file);

  char** lines;
  int line_count = makeargv(buffer, "\n", &lines);

  for (int i = 0; i < line_count; i++){
    if (!incrementCandidate(lines[i])) {
      addNewCandidate(lines[i]);
    }
  }
}

void print_list(){
  candidate* current = headNode->next;
  while(current != NULL) {
    printf("Candidate %s has %d votes\n", current->name, current->votes);
    current = current->next;
  }
}

void create_output(char* path) {
  char** directories;
  int size = makeargv(path, "/", &directories);
  char* filename = directories[size-1];
  strcat(filename, ".txt");
  char* pathname = malloc(sizeof(char)*255);
  sprintf(pathname, "%s/%s", path, filename);
  FILE* file;
  if (!(file = fopen(pathname, "w"))) {
      perror("fopen() error");
      exit(1);
  }

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

int main(int argc, char** argv) {

  if (argc < 2) {
    perror("Incorrect number of arguments\n");
    exit(1);
  }

  if (is_leaf(argv[1])) {
    //printf("%s contains a votes.txt file\n", argv[1]);
    count_votes(argv[1]);
    //print_list();
    create_output(argv[1]);
  } else {
    perror("Not a leaf node.\n");
  }

  return 0;
}
