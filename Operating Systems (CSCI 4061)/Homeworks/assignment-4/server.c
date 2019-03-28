/*
  login: starx013, nusse007
  date: 04/19/18
  name: Gregory Star, Malik Nusseibeh
  id: 5191430, 4978826
*/

#define _BSD_SOURCE
#define MAX_CONNECTIONS 5

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

typedef struct candidate {
  char* name;
  int votes;
  struct candidate* next;
} candidate;

typedef struct node{
  char* path;
  bool open;
  bool opened;
  char name[16];
  struct node* children[5];
  candidate* candidates;
  int numChildren;
  struct node* parent;
} node;

typedef struct tree{
  node* headNode;
} tree;

tree* dag;
pthread_mutex_t dag_mutex;

// add votes for the candidate, if the candidate doesn't exist in the
// region's linked list add them
void addCandidateVotes(char* name, int votes, candidate* headNode) {
  candidate* current = headNode;
  while (current != NULL) {
    current = current->next;
    if (current != NULL && !strcmp(current->name, name)) {
      // candidate found in region, add votes and exit
      current->votes += votes;
      return;
    }
  }

  // candidate not found in region
  current = headNode;
  while (current->next != NULL) {
    current = (current->next);
  }
  current->next = malloc(sizeof(candidate));
  current->next->name = name;
  current->next->votes = votes;
  current->next->next = NULL;
}


// //Combines incrementCandidate and addNewCandidate
// //Now only one function needs to be called
// //Not super efficient because it redoes the loop but whatever
// void processCandidate(char* candidateName, int votes, candidate* headNode) {
//   candidate* current = headNode;
//   while(current != NULL){
// 		current = (current->next);
//     if(current != NULL && strcmp(current->name, candidateName) == 0) {
//       break;
//     }
//
//   }
//   if(current == NULL) {
//     addCandidateVotes(candidateName, votes, headNode);
//   } else {
//     current->votes += votes;
//   }
// }

// Takes two candidate lists and merges the first one into the second one.
void mergeCandidateLists(candidate* child, candidate* headNode){
	candidate* current = child->next;
	while(current != NULL){
		char* name = current->name;
		int votes = current->votes;
		addCandidateVotes(name, votes, headNode);
		current = current->next;
	}
}

// remove votes from a candidate, this function assumes a legal subtraction
void removeCandidateVotes(char* name, int votes, candidate* headNode) {
  candidate* current = headNode;
  while (current != NULL) {
    current = current->next;
    if (current != NULL && !strcmp(current->name, name)) {
      current->votes -= votes;
      return;
    }
  }
}

// This function checks if every removal is valid, if any removal is invalid
// set's err_candidate to the name of candidate that caused illegal subtraction
bool legalRemoval(char* data, candidate* headNode, char* err_candidates) {
  char** candidates;
  bool flag = true;
  err_candidates[0] = '\0';
  int candidate_count = split(data, ',', &candidates);
  // go through each candidate in the data
  for (int i = 0; i < candidate_count; i++) {
    char** cand_vote;
    split(candidates[i], ':', &cand_vote);
    int votes = atoi(cand_vote[1]);

    candidate* current = headNode;
    bool legal = false;
    // check if the candidate is in the linked list
    while (current != NULL) {
      current = current->next;
      if (current != NULL && !strcmp(current->name, cand_vote[0])) {
        // check that the subtraction won't lead to negative votes
        if (current->votes > votes)
          legal = true;
        break;
      }
    }
    // if an illegal subtraction is found return false with name of candidate
    if (!legal) {
      // strcpy(err_candidates, cand_vote[0]);
      strcat(err_candidates, cand_vote[0]);
      strcat(err_candidates, " ");
      flag = false;
    }
  }
  free(candidates);
  candidate_count = split(err_candidates, ' ', &candidates);
  err_candidates[0] = '\0';
  for (int i = 0; i < candidate_count; i++) {
    strcat(err_candidates, candidates[i]);
    if (i < candidate_count-1)
      strcat(err_candidates, ",");
  }
  return flag;
}





// find the winner in the dag, assumes aggregation is complete
char* findWinner() {
  candidate* current = dag->headNode->candidates;
  char* winner = malloc(128);
  int votes = 0;
  while (current != NULL) {
    if (current->votes > votes) {
      strcpy(winner, current->name);
      votes = current->votes;
    }
    current = current->next;
  }
  return winner;
}

// Returns a string of candidates and votes
char* retrieveVotes(candidate* headNode) {
  char* votes = malloc(253);
  candidate* current = headNode->next;
  if (current != NULL)
    votes[0] = '\0';
  else
    sprintf(votes, "No votes.");
  while (current != NULL) {
    char* candidate_votes = malloc(253);
    sprintf(candidate_votes, "%s:%d", current->name, current->votes);
    strcat(votes, candidate_votes);
    current = current->next;
    if (current != NULL)
      strcat(votes, ",");
  }
  return votes;
}

// function to print a candidate list
void printCandidateList(candidate* headNode) {
  if (headNode != NULL) {
    candidate* current = headNode->next;
    while(current != NULL) {
      printf("\t\t\t   %s:%d\n", current->name, current->votes);
      current = current->next;
    }
  }
}

bool addNodeToParent(node* head, char* parentName, node* n){
  if(strcmp(head->name, parentName) == 0){
    head->children[head->numChildren] = n;
    head->numChildren++;
    n->parent = head;
    return true;
  } else if(head->numChildren == 0) {
    return false;
  } else {
    for(int i = 0; i < head->numChildren; i++){
      if(addNodeToParent(head->children[i], parentName, n)){
        return true;
      }
    }
    return false;
  }
}

// Returns node pointer with requested name
node* retrieveNode(node* head, char* nodeName){
  if(strcmp(head->name, nodeName) == 0){
    return head;
  } else if(head->numChildren == 0) {
    return NULL;
  } else {
    for(int i = 0; i < head->numChildren; i++){
      if(retrieveNode(head->children[i], nodeName) != NULL){
        return retrieveNode(head->children[i], nodeName);
      }
    }
    return NULL;
  }
}

void build_dag(char* filename) {
  FILE* file;
  if (!(file=fopen(filename, "r"))) {
    perror("fopen() error");
    exit(1);
  }

  dag = malloc(sizeof(tree));
  dag->headNode = malloc(sizeof(node));
  dag->headNode->candidates = malloc(sizeof(candidate));
  dag->headNode->numChildren = 0;


  fseek(file, 0, SEEK_END);
  int length = ftell(file);
  fseek(file, 0, SEEK_SET);
  char* buffer = malloc(sizeof(char)*length);
  fread(buffer, 1, length, file);

  char** lines;
  int line_count = split(buffer, '\n', &lines);


  for(int i = 0; i < line_count; i++){
    char* line = lines[i];
    char** words;
    int word_count = split(line, ':', &words);
    // if first row add root to dag
    if (!i)
      sprintf(dag->headNode->name, "%s", words[0]);
    for(int j = 1; j < word_count; j++){
      node* n = malloc(sizeof(node));
      n->numChildren = 0;
      strcpy(n->name, words[j]);
      n->open = false;
      n->opened = false;
      n->candidates = malloc(sizeof(candidate));
      addNodeToParent(dag->headNode, words[0], n);
    }
  }
}

void printDAG(node* current) {
  printf("\t%-15s -- %s\n", current->name,
      (current->open)?"open":((current->opened)?"closed":"unopened"));
  printCandidateList(current->candidates);
  if (current->numChildren) {
    for(int i = 0; i < current->numChildren; i++)
      printDAG(current->children[i]);
  }
}


// Check if all polls are closed
bool allPollsClosed(node* n, char* err_candidate) {
  if (n->open || !n->opened) {
    strcpy(err_candidate, n->name);
    return false;
  }
  if (n->numChildren) {
    for(int i = 0; i < n->numChildren; i++)
      if (!allPollsClosed(n->children[i], err_candidate))
        return false;
  }
  return true;
}

// All children of a given node will be open
// This will not reopen a poll or any of it's cildren
void openAllChildren(node* n) {
  if (n->opened) {
    return;
  } else if (!n->open) {
    n->open = true;
    n->opened = true;
  }
  if (n->numChildren) {
    for (int i = 0; i < n->numChildren; i++) {
      openAllChildren(n->children[i]);
    }
  }
}

// All children of a given node will be closed
void closeAllChildren(node* n) {
  if (n->open)
    n->open = false;
  if (n->numChildren) {
    for (int i = 0; i < n->numChildren; i++)
      closeAllChildren(n->children[i]);
  }
}

//Propogate new votes all the way up the dag.
void propogateResultsUp(node* current, candidate* newVotes){
  if(strcmp(current->name, dag->headNode->name) != 0){
    mergeCandidateLists(newVotes, current->parent->candidates);
    propogateResultsUp(current->parent, newVotes);
  }
}

// Command to open a region's polls
char* open_poll(char* region) {
  char* response = malloc(256);
  node* n = malloc(sizeof(node));
  if ((n = retrieveNode(dag->headNode, region)) != NULL) {

    // check if poll is already open
    if (n->open) {
      sprintf(response, "PF;%s open%c", region, '\0');

    // check if poll has been previously been opened
    } else if (n->opened) {
      sprintf(response, "RR;%s%c", region, '\0');

    } else {
      sprintf(response, "SC;%c", '\0');
      // open region and all it's children
      openAllChildren(n);
    }

  // region doesn't exist
  } else {
    sprintf(response, "NR;%s%c", region, '\0');
  }
  return response;
}

// Command to close a region's polls
char* close_poll(char* region) {
  char* response = malloc(256);
  node* n = malloc(sizeof(node));
  if ((n = retrieveNode(dag->headNode, region)) != NULL) {

    // check if poll is already closed
    if (!n->open) {
      sprintf(response, "PF;%s %s%c", region,
          (n->opened)?"closed":"unopened", '\0');

    } else {
      sprintf(response, "SC;%c", '\0');
      // close region and all it's children
      closeAllChildren(n);
    }

  // region doesn't exist
  } else {
    sprintf(response, "NR;%s%c", region, '\0');
  }
  return response;
}

// Command to find winner from root
char* find_winner() {
  char* response = malloc(256);
  char err_region[16];
  if (allPollsClosed(dag->headNode, err_region)) {
    char data[253];
    sprintf(data, "Winner:%s", findWinner());
    sprintf(response, "SC;%s%c", data, '\0');
  } else {
    sprintf(response, "RO;%s%c", err_region, '\0');
  }
  //printCandidateList(dag->headNode->candidates);
  return response;
}

// Command to count votes in a region
char* count_votes(char* region) {
  char* response = malloc(256);
  node* n = malloc(sizeof(region));
  if ((n = retrieveNode(dag->headNode, region)) != NULL) {
    char data[253];
    strcpy(data, retrieveVotes(n->candidates));
    sprintf(response, "SC;%s%c", data, '\0');
  } else {
    sprintf(response, "NR;%s%c", region, '\0');
  }
  return response;
}

// Command to add votes to a region
char* add_votes(char* region, char* data) {
  char* response = malloc(256);
  node* n = malloc(sizeof(node));
  candidate* newVotes = malloc(sizeof(candidate));
  if ((n = retrieveNode(dag->headNode, region)) != NULL) {

    // node that contains children is not a leaf
    if (n->numChildren) {
      sprintf(response, "NL;%s%c", region, '\0');

    // check if the region's poll is open
    } else if (!n->open) {
      sprintf(response, "RC;%s%c", region, '\0');

    // add votes
    } else {
      sprintf(response, "SC;%c", '\0');
      char** candidates;
      int candidate_count = split(data, ',', &candidates);
      // go through each candidate in data
      for (int i = 0; i < candidate_count; i++) {
        char** cand_vote;
        split(candidates[i], ':', &cand_vote);
        int votes = atoi(cand_vote[1]);
        //printf("adding %s %d\n", cand_vote[0], votes);
        // add the candidate's votes to the node's linked list
        addCandidateVotes(cand_vote[0], votes, newVotes);
        //addCandidateVotes(cand_vote[0], votes, n->candidates);

      }
      mergeCandidateLists(newVotes, n->candidates);
      propogateResultsUp(n, newVotes);

    }

  // region doesn't exist
  } else {
    sprintf(response, "NR;%s%c", region, '\0');
  }
  return response;
}

// Command to remove votes from a region
char* remove_votes(char* region, char* data) {
  char* response = malloc(256);
  node* n = malloc(sizeof(node));
  candidate* newVotes = malloc(sizeof(candidate));
  if ((n = retrieveNode(dag->headNode, region)) != NULL) {

    // node that contains children is not a leaf
    if (n->numChildren) {
      sprintf(response, "NL;%s%c", region, '\0');

    // check if the region's poll is open
    } else if (!n->open) {
      sprintf(response, "RC;%s%c", region, '\0');

    // remove votes
    } else {
      // candidate string in case of error
      char err_candidates[253];
      // check if the remove is a legal subtraction
      if (legalRemoval(data, n->candidates, err_candidates)) {
        sprintf(response, "SC;%c", '\0');
        char** candidates;
        int candidate_count = split(data, ',', &candidates);
        // go through each candidate in data
        for (int i = 0; i < candidate_count; i++) {
          char** cand_vote;
          split(candidates[i], ':', &cand_vote);
          int votes = atoi(cand_vote[1]);
          //printf("removing %s %d\n", cand_vote[0], votes);
          // remove the candidate's votes from the node's linked list
          addCandidateVotes(cand_vote[0], (-1) * votes, newVotes);
          //removeCandidateVotes(cand_vote[0], votes, n->candidates);
        }
        mergeCandidateLists(newVotes, n->candidates);
        propogateResultsUp(n, newVotes);

      // create response in case of illegal subtraction
      } else
        sprintf(response, "IS;%s%c", err_candidates, '\0');
    }

  // region doesn't exist
  } else {
    sprintf(response, "NR;%s%c", region, '\0');
  }
  return response;
}

char* add_region(char* parent_region, char* new_region) {
  char* response = malloc(256);
  node* n = malloc(sizeof(node));
  if ((n = retrieveNode(dag->headNode, parent_region)) != NULL) {
    node* new_node = malloc(sizeof(node));
    new_node->numChildren = 0;
    strcpy(new_node->name, new_region);
    new_node->open = false;
    new_node->opened = false;
    new_node->candidates = malloc(sizeof(candidate));
    addNodeToParent(n, parent_region, new_node);
    sprintf(response, "SC;%c", '\0');
  } else {
    sprintf(response, "NR;%s%c", parent_region, '\0');
  }
  return response;
}

// Handle a client request by determining which function to call
char* handle_request(char* request_str, char* clientIP, int clientPort) {
  char** request;
  split(request_str, ';', &request);
  removeSpaces(request[1]);
  printf("Request received from client at %s:%d, %s %s %s\n",
      clientIP, clientPort, request[0], request[1], request[2]);

  if (!strcmp("RW", request[0])) {
    return find_winner();

  } else if (!strcmp("CV", request[0])) {
    return count_votes(request[1]);

  } else if (!strcmp("OP", request[0])) {
    return open_poll(request[1]);

  } else if (!strcmp("AV", request[0])) {
    return add_votes(request[1], request[2]);

  } else if (!strcmp("RV", request[0])) {
    return remove_votes(request[1], request[2]);

  } else if (!strcmp("CP", request[0])) {
    return close_poll(request[1]);

  } else if (!strcmp("AR", request[0])) {
    return add_region(request[1], request[2]);

  } else {
    char* response = malloc(256);
    sprintf(response, "UC;%s%c", request[0], '\0');
    return response;
  }
}


typedef struct thread_params {
  char* IP;
  int port;
  int sock;
} thread_params;

void *connection_handler(void* params) {
  thread_params* p = (thread_params*)params;
  char* IP = p->IP;
  int port = p->port;
  int sock = p->sock;

  while (1) {
    char request[256];
    // if (read(sock, &request, 256) == 0)
    //   break;
    if (recv(sock, request, 256, 0) == 0)
      break;
    char response[256];
    pthread_mutex_lock(&dag_mutex);
    strcpy(response, handle_request(request, IP, port));
    pthread_mutex_unlock(&dag_mutex);
    //write(sock, &response, 256);
    send(sock, response, 256, 0);
    char** response_s;
    split(response, ';', &response_s);
    printf("Sending response to client at %s:%d, %s %s\n",
        IP, port, response_s[0], response_s[1]);
  }

  // printf("\n");
  // pthread_mutex_lock(&dag_mutex);
  // printDAG(dag->headNode);
  // pthread_mutex_unlock(&dag_mutex);
  // printf("\n");
  // close(sock);
  printf("Closed connection with client at %s:%d\n", IP, port);
}

int main(int argc, char** argv) {
  int sock, server_port;
  char dag_filename[256];

  if (argc < 3) {
    fprintf(stderr, "Error: server requires 2 input parameter\n");
    exit(0);
  }

  server_port = atoi(argv[2]);
  sprintf(dag_filename, "%s", argv[1]);

  build_dag(dag_filename);
  //printDAG(dag->headNode);
  pthread_mutex_init(&dag_mutex, NULL);

  sock = socket(AF_INET, SOCK_STREAM, 0);
  struct sockaddr_in servAddress;
  servAddress.sin_family = AF_INET;
  servAddress.sin_port = htons(server_port);
  servAddress.sin_addr.s_addr = htonl(INADDR_ANY);
  bind(sock, (struct sockaddr *) &servAddress, sizeof(servAddress));

  listen(sock, MAX_CONNECTIONS);
  printf("Server listening on port %d\n", server_port);

  pthread_t thread_id;

  while(1){
    int fd;
    struct sockaddr_in clientAddress;
    socklen_t size = sizeof(struct sockaddr_in);

    // accept connection
    if ((fd = accept(sock, (struct sockaddr *) &clientAddress, &size)) < 0) {
      perror("Failed to accept connection");
      continue;
    }

    char clientIP[16];
    int clientPort = ntohs(clientAddress.sin_port);
    sprintf(clientIP, "%s", inet_ntoa(clientAddress.sin_addr));
    printf("Connection initiated from client at %s:%d\n", clientIP, clientPort);

    // create thread params
    thread_params params = {clientIP, clientPort, fd};

    // spawn thread to handle client requests
    if (pthread_create(
        &thread_id, NULL, connection_handler, (void*) &params) < 0) {
      perror("Failed to create thread");
      continue;
    }
  }
  close(sock);
  return 0;
}
