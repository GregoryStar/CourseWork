/*
  login: starx013, nusse007
  date: 04/19/18
  name: Gregory Star, Malik Nusseibeh
  id: 5191430, 4978826
*/

#define _BSD_SOURCE

#include "util.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <pthread.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include <stdbool.h>

char path[1024];

typedef struct candidate {
  char* name;
  int votes;
  struct candidate* next;
} candidate;

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

char* read_data(char* filename) {
  FILE* file;
  char filepathname[1024];
  sprintf(filepathname, "%s%s", path, filename);
  //printf("filename: %s\n", filepathname);
  if (!(file=fopen(filepathname, "r"))) {
    perror("fopen() error");
    return NULL;
  }

  fseek(file, 0, SEEK_END);
  int length = ftell(file);
  fseek(file, 0, SEEK_SET);
  char* buffer = malloc(sizeof(char)*length + 1);
  fread(buffer, 1, length, file);
  fclose(file);
  buffer[length] = '\0';

  //printf("Buffer %s\n", buffer);

  char** lines;
  int line_count = split(buffer, '\n', &lines);
  //int line_count = makeargv(buffer, "\n", &lines);
  //printf("lengthOfFile: %d, Line count: %d\n", length, line_count);

  candidate* headNode = malloc(sizeof(candidate));
  headNode->next = NULL;

  int num_candidates = 0;
  for (int i = 0; i < line_count; i++) {
    if (!incrementCandidate(lines[i], headNode)) {
      addNewCandidate(lines[i], headNode);
      num_candidates++;
    }
  }
  char* data = malloc(sizeof(char)*num_candidates*128);
  strcpy(data, "");

  candidate* current = headNode->next;
  while(current != NULL) {
    char* candidate_str = malloc(sizeof(char)*128);
    sprintf(candidate_str, "%s:%d", current->name, current->votes);
    strcat(data, candidate_str);
    current = current->next;
    if (current!=NULL) {
      strcat(data, ",");
    }
    free(candidate_str);
  }

  //freemakeargv(lines);

  return data;
}


char* request_code(char* request_str) {
  char** request;
  split(request_str, ' ', &request);
  char* request_code = malloc(256);
  char* data;

  if (!strcmp("Return_Winner", request[0])) {
    sprintf(request_code, "RW;%-15s;%c", "", '\0');

  } else if (!strcmp("Count_Votes", request[0])) {
    sprintf(request_code, "CV;%-15s;%c", request[1], '\0');

  } else if (!strcmp("Open_Polls", request[0])) {
    sprintf(request_code, "OP;%-15s;%c", request[1], '\0');

  } else if (!strcmp("Add_Votes", request[0])) {
    data = read_data(request[2]);
    if (data == NULL)
      request_code = NULL;
    else
      sprintf(request_code, "AV;%-15s;%s%c", request[1], data, '\0');

  } else if (!strcmp("Remove_Votes", request[0])) {
    data = read_data(request[2]);
    if (data == NULL)
      request_code = NULL;
    else
      sprintf(request_code, "RV;%-15s;%s%c", request[1], data, '\0');

  } else if (!strcmp("Close_Polls", request[0])) {
    sprintf(request_code, "CP;%-15s;%c", request[1], '\0');

  } else if (!strcmp("Add_Region", request[0])) {
    if (request[2] == NULL)
      request_code = NULL;
    else
      sprintf(request_code, "AR;%-15s;%s%c", request[1], request[2], '\0');

  } else {
    fprintf(stderr, "Error: Invalid Request");
    free(request_code);
    request_code = NULL;
  }
  return request_code;
}



int main(int argc, char** argv) {
  int sock, server_port;
  struct sockaddr_in address;
  FILE* req_file;

  if (argc < 4) {
    fprintf(stderr, "Error: client requires 3 input parameter\n");
    exit(0);
  }

  server_port = atoi(argv[3]);

  if (!(req_file=fopen(argv[1], "r"))) {
    perror("fopen() error");
    exit(1);
  }

  // find path of files
  char** path_dir;
  int path_dir_length = split(argv[1], '/', &path_dir);
  for(int i = 0; i<(path_dir_length-1); i++) {
    strcat(path, path_dir[i]);
    strcat(path, "/");
  }
  printf("%s\n",path);

  sock = socket(AF_INET, SOCK_STREAM, 0);
  address.sin_family = AF_INET;
  address.sin_port = htons(server_port);
  address.sin_addr.s_addr = inet_addr(argv[2]);

  if (connect(sock, (struct sockaddr*) &address, sizeof(address)) == 0) {

    printf("Initiated connection with server at %s:%d\n", argv[2], server_port);

    fseek(req_file, 0, SEEK_END);
    int length = ftell(req_file);
    fseek(req_file, 0, SEEK_SET);
    char* buffer = malloc(sizeof(char)*length);
    fread(buffer, 1, length, req_file);

    char** lines;
    int line_count = split(buffer, '\n', &lines);

    char request[256];
    char response[256];

    for (int i = 0; i < line_count; i++) {
      strcpy(request, request_code(lines[i]));
      if (request == NULL) {
        printf("Invalid Request\n");
        continue;
      }

      char** request_s;
      split(request, ';', &request_s);
      //write(sock, &request, 256);
      send(sock, request, 256, 0);
      removeSpaces(request_s[1]);
      printf("Sending request to server: %s %s %s\n", request_s[0], request_s[1], request_s[2]);

      //read(sock, &response, 256);
      recv(sock, response, 256, 0);
      char** response_s;
      split(response, ';', &response_s);
      removeSpaces(response_s[1]);
      printf("Received response from server: %s %s\n", response_s[0], response_s[1]);
      //handle_response(response);
    }

    close(sock);
    printf("Close connection with server at %s:%d\n", argv[2], server_port);

  } else {
    perror("Connection failed!");
  }

  return 0;
}
