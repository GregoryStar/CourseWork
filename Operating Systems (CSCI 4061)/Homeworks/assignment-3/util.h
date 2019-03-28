#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct params {
	char* name;
	char* infile;
	char* outfile;
  char* logtxt;
} params;

typedef struct node {
	params* item;
	struct node* next;
} node;

typedef struct queue {
  node* head;
  node* tail;
} queue;

int split(char* string, char delim_char, char*** string_list) {
  char *string_copy, *delim_copy, *found;
  char delim[2];
  delim[0] = delim_char;
  delim[1] = '\0';

  int length = strlen(string);

  string_copy=strdup(string);
  delim_copy=strdup(delim);

  int size = 0;
  while ( (found = strsep(&string_copy, delim_copy)) != NULL)
    size++;
  string_copy=strdup(string);

  *string_list = malloc(size*sizeof(char*));

  for (int i = 0; i < size; i++)
    *((*string_list)+i) = strsep(&string_copy, delim_copy);

  if (string[length-1] == delim_char || !isalnum(string[length-1]))
    size--;

  return size;
}

params* popFromQueue(queue* q){
  //Special condition for the head
  if(q->head->next == NULL){
    params* item = q->head->item;
    q->head = NULL;
    return item;
  }

  node* n = q->head;
	while(n->next->next != NULL){
		n = n->next;
	}

	params* item = n->next->item;
  n->next = NULL;
	return item;
}

int numElements(queue* q){
  if(q->head == NULL){
    return 0;
  }
  node* current = q->head;
	int i = 1;
	while(current->next != NULL){
		current = current->next;
		i++;
	}
	return i;
}

void addToQueue(char* fileName, char* in, char* out, queue* q){
	node* n = malloc(sizeof(node));
	n->item = malloc(sizeof(params));
  n->item->name = malloc(1024);
  strcpy(n->item->name, fileName);

	n->item->infile = in;
	n->item->outfile = out;
  n->next = NULL;

  if(!(q->tail)){
    q->head = q->tail = n;
    numElements(q);
    return;
  }

  q->tail->next = n;
  q->tail = n;
  numElements(q);
}

char decrypt_char(char c){
	int offset = 0;
	if(c >= 65 && c <= 90) {
		//Uppercase
		offset = 65;
	} else if (c >= 97 && c <= 122) {
		//Lowercase
		offset = 97;
	} else {
		//Not alphebetic
		return c;
	}

	char output = (((c - offset) + 2) % 26) + offset;
	return output;
}
