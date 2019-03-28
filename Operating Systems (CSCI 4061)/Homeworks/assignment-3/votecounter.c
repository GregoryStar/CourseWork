/*
  login: starx013, nusse007
  date: 04/03/18
  name: Gregory Star, Malik Nusseibeh
  id: 5191430, 4978826
*/
#define _BSD_SOURCE

#include "util.h"
#include <dirent.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <pthread.h>
#include <stdbool.h>

pthread_mutex_t log_mutex;

typedef struct candidate {
  char* name;
  int votes;
  struct candidate* next;
} candidate;

typedef struct parentMutex {
	char* name;
	pthread_mutex_t mutex;
	pthread_cond_t cond;
} parentMutex;

parentMutex** parentMutexList;
int parentMutexLength;

int findIndexByName(char* name) {
	for (int i=0; i<parentMutexLength; i++) {
		if (!strcmp(parentMutexList[i]->name, name)) {
			return i;
		}
	}
	return -1;
}

void decrypt_file(char* infile, char* outfile) {
  FILE *file = fopen(infile, "r");
  fseek(file, 0, SEEK_END);
  int length = ftell(file);
  fseek(file, 0, SEEK_SET);
  char *buffer = malloc(sizeof(char) * length);
  fread(buffer, 1, length, file);
  fclose(file);

  char *decrypted_buffer = malloc(sizeof(char) * length+1);
  for (int i = 0; i < length; i++) {
    decrypted_buffer[i] = decrypt_char(buffer[i]);
  }

  FILE *out;
  if (!(out=fopen(outfile, "w"))) {
    perror("fopen() error");
    exit(1);
  }
  fwrite(decrypted_buffer, 1, length, out);
  fclose(out);
}

void create_dir(char *pathname) {
  struct stat st = {0};
  if (stat(pathname, &st) == -1)
    mkdir(pathname, 0700);
}

int stringIn(char* string, char** list, int size) {
  for (int i = 0; i < size; i++) {
    if (strcmp(string, list[i]) == 0) {
      return i;
    }
  }
  return -1;
}


//Recursively creates the file structure
void build_dir(int lineNum, char** parents, char** lines, int lineCount, char* pathname, char* input_name, queue *q) {
  char *child = malloc(1024);
  child[0] = '\0';

  char* new_pathname = malloc(1024);
  new_pathname[0] = '\0';
  strcpy(new_pathname, pathname);
  strcat(new_pathname, "/");
  strcat(new_pathname, parents[lineNum]);
  create_dir(new_pathname);

  char** words;
  int wordCount = split(lines[lineNum], ':', &words);
  for (int i = 1; i < wordCount; i++) {
    strcpy(child, words[i]);
    int newLineNum;
    newLineNum = stringIn(child, parents, lineCount);
    if (newLineNum > -1)
      build_dir(newLineNum, parents, lines, lineCount, new_pathname, input_name, q);
    else {
      char *infile = malloc(1024);
      infile[0] = '\0';
      char* outfile = malloc(1024);
      outfile[0] = '\0';
      strcpy(infile, input_name);
      strcat(infile, "/");
      strcat(infile, child);
      strcpy(outfile, new_pathname);
      strcat(outfile, "/");
      strcat(outfile, child);
      strcat(outfile, ".txt");
      //printf("Name: %s\n", child);
			addToQueue(child, infile, outfile, q);
    }
  }
}

//Reads input file to prepare for creating directory. Calls build_dir()
void create_outdir(char *filename, char *pathname, char *input_name, queue *q) {
  FILE *file;
  if(!(file = fopen(filename, "r"))){
    fprintf(stderr, "fopen() failed");
    exit(1);
  }
  fseek(file, 0, SEEK_END);
  int length = ftell(file);
  fseek(file, 0, SEEK_SET);
  char *buffer = malloc(sizeof(char) * length);
  fread(buffer, 1, length, file);
  //INPUT HAS BEEN READ INTO BUFFER
  fclose(file);

  char** lines;
  int lineCount = split(buffer, '\n', &lines);
  //printf("lineCount: %d\n", lineCount);
  char** parents = malloc(lineCount*sizeof(char*));

	parentMutexList = malloc(sizeof(parentMutex)*lineCount);
	parentMutexLength = lineCount;

  for (int i = 0; i < lineCount; i++) {

    char** words;
    split(lines[i], ':', &words);
    parents[i] = malloc(1024);
    parents[i][0] = '\0';
    strcpy(parents[i], words[0]);
    //printf("parent: %s\n", parents[i]);
		parentMutexList[i] = malloc(sizeof(parentMutex));
		parentMutexList[i]->name = malloc(1024);
    parentMutexList[i]->name[0] = '\0';

		pthread_mutex_init(&parentMutexList[i]->mutex, NULL);
		strcpy(parentMutexList[i]->name, parents[i]);
  }

  build_dir(0, parents, lines, lineCount, pathname, input_name, q);
}

/****************************************
  COUNT LEAF FUNCTIONS
*****************************************/

pthread_mutex_t print_lock;

void addNewCandidate(char* newName, candidate* headNode){
  candidate* current = headNode;
  while(current->next != NULL){
    current = (current->next);
  }
 current->next = malloc(sizeof(candidate));
 current->next->name = newName;
 current->next->votes = 1;
 current->next->next = NULL;
}

bool incrementCandidate(char* candidateName, candidate* headNode){
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

void count_votes(char* filename, candidate* headNode) {
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

  char** lines;
  int line_count = split(buffer, '\n', &lines);
	//TODO: resolve the issue with line count.
	//line_count = length/2;

  for (int i = 0; i < line_count; i++){
    if (!incrementCandidate(lines[i], headNode)) {
      addNewCandidate(lines[i], headNode);
    }
  }
}

//////////////////////////////////////////////////////////////////////////////
//THIS AREA IS RESPONSIBLE FOR AGGREGATION ***********************************
///////////////////////////////////////////////////////////////////////////////

//If a candidate isn't already in the list, add it
void addCandidateVotes(char* newName, int votes, candidate* headNode) {
  candidate* current = headNode;
  while(current->next != NULL){
    current = (current->next);
  }
  current->next = malloc(sizeof(candidate));
  current->next->name = newName;
  current->next->votes = votes;
  current->next->next = NULL;
}

//Combines incrementCandidate and addNewCandidate
//Now only one function needs to be called
//Not super efficient because it redoes the loop but whatever
void processCandidate(char* candidateName, int votes, candidate* headNode) {
  candidate* current = headNode;
  while(current != NULL){
		current = (current->next);
    if(current != NULL && strcmp(current->name, candidateName) == 0) {
      break;
    }

  }
  if(current == NULL) {
    addCandidateVotes(candidateName, votes, headNode);
  } else {
    current->votes += votes;
  }
}

void mergeCandidateLists(candidate* child, candidate* headNode){
	candidate* current = child->next;
	while(current != NULL){
		char* name = current->name;
		int votes = current->votes;
		processCandidate(name, votes, headNode);
		current = current->next;
	}
}

void parseChildOutput(char* pathname, candidate* childNode) {
	candidate* parentNode = malloc(sizeof(candidate));
	parentNode->next = NULL;

	FILE* file;
	if ((file = fopen(pathname, "r"))) {
	  fseek(file, 0, SEEK_END);
	  int length = ftell(file);
	  fseek(file, 0, SEEK_SET);

	  char* buffer = malloc(sizeof(char)*length);
	  fread(buffer, 1, length, file);
	  fclose(file);

	  //Break the file into an array of strings by delimiting ','
	  char** entries;
	  int numEntries = split(buffer, '\n', &entries);
    numEntries--;

    //printf("%s\n", pathname);

    char** winner;
    split(entries[numEntries-1], ':', &winner);
    if (!strcmp("WINNER", winner[0])) {
      numEntries--;
      //printf("Remove Winner\n");
    }

	  //Populate candidate list
	  for(int i = 0; i < numEntries; i++){
	    //split the candidate from the count_votes
	    char** subEntries;
	    int numSubEntries = split(entries[i], ':', &subEntries);
	    char* name = subEntries[0];
	    int votes = atoi(subEntries[1]);
      //printf("%s:%d\n", name, votes);
	    processCandidate(name, votes, parentNode);
	  }
	}
	mergeCandidateLists(childNode, parentNode);

	file = fopen(pathname, "w");

	//write back to file
	candidate* current = parentNode->next;
	while(current != NULL){
		fprintf(file, "%s:%d", current->name, current->votes);
		//if (current->next != NULL)
			fprintf(file, "\n");
		current = (current->next);
	}

	fclose(file);
	chmod(pathname, 0700);
}

void find_winner(char* filename) {
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

	char* winner = malloc(1024);
  winner[0] = '\0';
	int highestCount = 0;
   //Break the file into an array of strings by delimiting ','
  char** entries;
  int numEntries = split(buffer, '\n', &entries);
  //printf("numEntries: %d\n", numEntries);

  //Populate candidate list
  for(int i = 0; i < numEntries; i++){
  //split the candidate from the count_votes
    char** subEntries;
    int numSubEntries = split(entries[i], ':', &subEntries);
    char* name = subEntries[0];
    int votes = atoi(subEntries[1]);
    if (votes > highestCount) {
    	highestCount = votes;
    	strcpy(winner, name);
      //printf("new winner: %s:%d\n", winner, highestCount);
    }
	}

	file = fopen(filename, "a");
	fprintf(file, "WINNER:%s\n", winner);
	fclose(file);
}

//Recursively propogates results up (overrides files)
void propogate(char* filename, candidate* headNode) {
	char* pathname = malloc(1024);
  pathname[0] = '\0';
  char* path = malloc(1024);
  path[0] = '\0';
	strcpy(pathname, "");
	char** parents;
	char* parentName = malloc(1024);
  parentName[0] = '\0';
	int parent_count = split(filename, '/', &parents);
	for (int i = 0; i < parent_count-1; i++) {
		strcat(pathname, parents[i]);
    strcpy(path, pathname);
		strcat(pathname, "/");
		if (i == parent_count-2) {
			strcpy(parentName, parents[i]);
			strcat(pathname, parents[i]);
			strcat(pathname, ".txt");
		}
	}

	int index = findIndexByName(parentName);
	if (index == -1){
		fprintf(stderr, "CATASTROPHIC ERROR");
		exit(1);
	}

	pthread_mutex_lock(&parentMutexList[index]->mutex);
  //printf("This is a test\n");
	parseChildOutput(pathname, headNode);
	pthread_mutex_unlock(&parentMutexList[index]->mutex);

  if (index > 0) {
    propogate(path, headNode);
  } else {
    //return;
    pthread_mutex_lock(&parentMutexList[index]->mutex);
    find_winner(pathname);
    pthread_mutex_unlock(&parentMutexList[index]->mutex);
  }
  return;
}

void* countAndPropogate(void* args){
  FILE* logfile;
  params* p = (params*)args;
  char* infile = p->infile;
  char* outfile = p->outfile;
  char* name = p->name;
  char* logtxt = p->logtxt;
  pthread_t tid = pthread_self();

  char** names;
  int length = split(outfile, '/', &names);
  split(names[length-1], '.', &names);
  name = names[0];

  //printf("Still ok\n");
  pthread_mutex_lock(&log_mutex);
  logfile = fopen(logtxt, "a");
  fprintf(logfile, "%s:%ld:start\n", name, tid);
  fclose(logfile);
  pthread_mutex_unlock(&log_mutex);

  decrypt_file(infile, outfile);

  candidate* headNode = malloc(sizeof(candidate));
	headNode->next = NULL;
  count_votes(outfile, headNode);

	propogate(outfile, headNode);

  pthread_mutex_lock(&log_mutex);
  logfile = fopen(logtxt, "a");
  fprintf(logfile, "%s:%ld:end\n", name, tid);
  fclose(logfile);
  pthread_mutex_unlock(&log_mutex);
}

int main(int argc, char** argv) {
  char *dag_file, *input_name, *output_name;
  int nthreads = 4;

  if (argc < 3) {
    fprintf(stderr, "Error: votecounter requires 3 input arguements\n");
    exit(1);
  }

  /*
  if (argv[4] != NULL) {
    nthreads = atoi(argv[4]);
  }*/

  dag_file = argv[1];
  input_name = argv[2];
  output_name = argv[3];

  create_dir(output_name);


  char* logtxt = malloc(1024);
  logtxt[0] = '\0';
  pthread_mutex_init(&log_mutex, NULL);
  strcpy(logtxt, output_name);
  strcat(logtxt, "/log.txt");
  FILE* logfile = fopen(logtxt, "w");
  fclose(logfile);
  //printf("\n");
  //fflush(stdout);

	queue* files = malloc(sizeof(queue));
  files->head = NULL;
  create_outdir(dag_file, output_name, input_name, files);

  //printf("test1\n");
	int queueSize = numElements(files);
  //printf("Test\n");
	pthread_t threads[queueSize];
	for(int i = 0; i < queueSize; i++){
		params *p = (params*)popFromQueue(files);
    p->logtxt = logtxt;
    //printf("Thread Created\n");
		pthread_create(&threads[i], NULL, countAndPropogate, (void*) p);
	}
  //printf("test2\n");
  //while()

  for (int i = 0; i < queueSize; i++){
		pthread_join(threads[i], NULL);
	}

  return 0;
}
