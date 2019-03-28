#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>

// typedef struct params {
// 	char* name;
// 	char* infile;
// 	char* outfile;
//   char* logtxt;
// } params;
//
// typedef struct node {
// 	params* item;
// 	struct node* next;
// } node;
//
// typedef struct queue {
//   node* head;
//   node* tail;
// } queue;

void removeSpaces(char *str)
{
  // To keep track of non-space character count
  int count = 0;

  // Traverse the given string. If current character
  // is not space, then place it at index 'count++'
  for (int i = 0; str[i]; i++)
    if (str[i] != ' ')
      str[count++] = str[i];// here count is
                            // incremented
  str[count] = '\0';
}

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

  if (string[length-1] == delim_char /*|| !isalnum(string[length-1])*/)
    size--;

  return size;
}

void freemakeargv(char **argv) {
   if (argv == NULL)
      return;
   if (*argv != NULL)
      free(*argv);
   free(argv);
}

int makeargv(const char *s, const char *delimiters, char ***argvp) {
   int error;
   int i;
   int numtokens;
   const char *snew;
   char *t;

   if ((s == NULL) || (delimiters == NULL) || (argvp == NULL)) {
      errno = EINVAL;
      return -1;
   }
   *argvp = NULL;
   snew = s + strspn(s, delimiters);
   if ((t = malloc(strlen(snew) + 1)) == NULL)
      return -1;
   strcpy(t,snew);
   numtokens = 0;
   if (strtok(t, delimiters) != NULL)
      for (numtokens = 1; strtok(NULL, delimiters) != NULL; numtokens++) ;

   if ((*argvp = malloc((numtokens + 1)*sizeof(char *))) == NULL) {
      error = errno;
      free(t);
      errno = error;
      return -1;
   }

   if (numtokens == 0)
      free(t);
   else {
      strcpy(t,snew);
      **argvp = strtok(t,delimiters);
      for (i=1; i<numtokens; i++)
         *((*argvp) +i) = strtok(NULL,delimiters);
   }
   *((*argvp) + numtokens) = NULL;
   return numtokens;
}


// params* popFromQueue(queue* q){
//   //Special condition for the head
//   if(q->head->next == NULL){
//     params* item = q->head->item;
//     q->head = NULL;
//     return item;
//   }
//
//   node* n = q->head;
// 	while(n->next->next != NULL){
// 		n = n->next;
// 	}
//
// 	params* item = n->next->item;
//   n->next = NULL;
// 	return item;
// }
//
// int numElements(queue* q){
//   if(q->head == NULL){
//     return 0;
//   }
//   node* current = q->head;
// 	int i = 1;
// 	while(current->next != NULL){
// 		current = current->next;
// 		i++;
// 	}
// 	return i;
// }
//
// void addToQueue(char* fileName, char* in, char* out, queue* q){
// 	node* n = malloc(sizeof(node));
// 	n->item = malloc(sizeof(params));
//   n->item->name = malloc(1024);
//   strcpy(n->item->name, fileName);
//
// 	n->item->infile = in;
// 	n->item->outfile = out;
//   n->next = NULL;
//
//   if(!(q->tail)){
//     q->head = q->tail = n;
//     numElements(q);
//     return;
//   }
//
//   q->tail->next = n;
//   q->tail = n;
//   numElements(q);
// }
//
// char decrypt_char(char c){
// 	int offset = 0;
// 	if(c >= 65 && c <= 90) {
// 		//Uppercase
// 		offset = 65;
// 	} else if (c >= 97 && c <= 122) {
// 		//Lowercase
// 		offset = 97;
// 	} else {
// 		//Not alphebetic
// 		return c;
// 	}
//
// 	char output = (((c - offset) + 2) % 26) + offset;
// 	return output;
// }
