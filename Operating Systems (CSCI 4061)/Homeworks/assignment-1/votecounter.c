/*
 * VCforStudents.c
 *
 *  Created on: Feb 2, 2018
 *      Author: ayushi
 */

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <stdlib.h>
#include "makeargv.h"
#include "sys/stat.h"
#include <stdbool.h>
#include <sys/wait.h>

#define MAX_NODES 100

//Global Variables
int numCandidates = 0;
char** candidates;
char* strnumCandidates;

//Function signatures
int parseInput(char *filename, node_t *n);
int parseInputLine(char *s, node_t *n, int lineNum);
void execNodes(node_t *n, int numNodes);




bool doesCycleExist(int* openSet, int openSetSize, node_t* universe, int currentNodeID){
	//check that the current node doesn't point to a predecessor
	for(int i = 0; i < openSetSize; i++){
		if(currentNodeID == openSet[i]){
			return true;
		}
	}

	node_t currentNode = universe[currentNodeID];
	int num_children = currentNode.num_children;

	//for each child of the current node, call the same function;
	bool returnable = false;
	for(int i = 0; i < num_children; i++){
		int* newOpenSet = malloc(sizeof(int) * (openSetSize + 1));
		int newOpenSetSize = openSetSize + 1;
		for(int j = 0; j < openSetSize; j++){
			newOpenSet[j] = openSet[j];
		}
		newOpenSet[openSetSize] = currentNode.id;
		returnable = returnable || doesCycleExist(newOpenSet, newOpenSetSize, universe, currentNode.children[i]);
	}

	return returnable;

}


/**Function : parseInput
 * Arguments: 'filename' - name of the input file
 * 			  'n' - Pointer to Nodes to be allocated by parsing
 * Output: Number of Total Allocated Nodes
 * About parseInput: parseInput is supposed to
 * 1) Open the Input File [There is a utility function provided in utility handbook]
 * 2) Read it line by line : Ignore the empty lines [There is a utility function provided in utility handbook]
 * 3) Call parseInputLine(..) on each one of these lines
 ..After all lines are parsed(and the DAG created)
 4) Assign node->"prog" ie, the commands that each of the nodes has to execute
 For Leaf Nodes: ./leafcounter <arguments> is the command to be executed.
 Please refer to the utility handbook for more details.
 For Non-Leaf Nodes, that are not the root node(ie, the node which declares the winner):
 ./aggregate_votes <arguments> is the application to be executed. [Refer utility handbook]
 For the Node which declares the winner:
 This gets run only once, after all other nodes are done executing
 It uses: ./find_winner <arguments> [Refer utility handbook]
 */
int parseInput(char *filename, node_t *n){
	//READ IN THE INPUT
	FILE* f = fopen(filename, "r");
	fseek(f, 0, SEEK_END);
	int length = ftell(f);
	fseek(f, 0, SEEK_SET);
	char* buffer = malloc(sizeof(char) * length);
	fread(buffer, 1, length, f);
	//THE INPUT HAS NOW BEEN READ INTO BUFFER

	//BUFFER GETS SPLIT INTO LINES
	char** lines;
	int lineCount = makeargv(buffer, "\n", &lines);


	//REMOVE COMMENTED LINES
	int newLineCount = 0;
	bool* commented = malloc(sizeof(bool)*lineCount);
	for(int i = 0; i < lineCount; i++){
		if(lines[i][0] == '#' || lines[i][0] == '\n' || lines[i][0] == '\0'){
			commented[i] = true;
		} else {
			commented[i] = false;
			newLineCount++;
		}
	}

	char** newLines = malloc(sizeof(char*)*newLineCount);
	for (int i = 0, j=0; i < lineCount; i++){
		if(!commented[i]){
			newLines[j] = lines[i];
			j++;
		}
	}


	//GET THE NUMBER OF NODES
	char** secondLine;
	int numNodes = makeargv(newLines[1], " ", &secondLine);

	//CREATE A NODE POINTER ARRAY OF THAT SIZE
	node_t* nodes = malloc(sizeof(node_t) * numNodes);


	//PARSEINPUTLINE WILL HAVE TO MAKE SPECIAL CASES FOR 0 AND 1
	printf("%d\n", newLineCount);
	for(int i = 0; i < newLineCount; i++){
		parseInputLine(newLines[i], nodes, i);
	}
	int* openSet = malloc(sizeof(int));
	bool hasCycle = doesCycleExist(openSet, 0, nodes, nodes[0].id);
	if(hasCycle){
		fprintf(stderr, "ERROR: Contains a cycle!\n");
		exit(1);
	} else {
		//printf("Does not contain a cycle!\n");
		execNodes(nodes, numNodes);
	}
}





/**Function : parseInputLine
 * Arguments: 's' - Line to be parsed
 * 			  'n' - Pointer to Nodes to be allocated by parsing
 * Output: Number of Region Nodes allocated
 * About parseInputLine: parseInputLine is supposed to
 * 1) Split the Input file [Hint: Use makeargv(..)]
 * 2) Recognize the line containing information of
 * candidates(You can assume this will always be the first line containing data).
 * You may want to store the candidate's information
 * 3) Recognize the line containing "All Nodes"
 * (You can assume this will always be the second line containing data)
 * 4) All the other lines containing data, will show how to connect the nodes together
 * You can choose to do this by having a pointer to other nodes, or in a list etc-
 * */
int parseInputLine(char *s, node_t *n, int lineNum){
	char** currentLine;
	int numWords = makeargv(s, " ", &currentLine);

	if(lineNum == 0){
		//TODO: OUTPUT ERROR IF THIS FAILS
		//checkFirstLineFormat(currentLine);
		numCandidates = atoi(currentLine[0]);

		if(numCandidates != numWords-1) {
			fprintf(stderr, "WARNING: Number of specified candidates does not match number of listed candidates\n");
			numCandidates = numWords-1;
		}


		strnumCandidates = malloc(sizeof(char)*4);
		sprintf(strnumCandidates, "%d", numCandidates);
		//strnumCandidates = (currentLine[0]);
		candidates = currentLine++;
		//ASSUMING THE FORMAT WAS CORRECT
		//TODO: READ IN CANDIDATES AND # OF CANDIDATES
	} else if (lineNum == 1){
		for(int i = 0; i < numWords; i++){
			n[i].name = currentLine[i];
			n[i].id = i;
			n[i].num_children = 0;
			//Uncomment printf to test that name is really in the node
			//printf("%s\n", (n[i].name));
		}
	} else {
		if(numWords < 3){
			fprintf(stderr, "ERROR: %s has no children but is formatted as a parent!\n", currentLine[0]);
			exit(1);
		}
		//Find the parent node id
		int k = 0;
		while(strcmp(currentLine[0], n[k].name) != 0){
			k++;
		}

		//Add all of the ids of the children of the node to the children array
		for(int i = 2; i < numWords; i++){
			//Skip the colon
			if(i != 1){
				int j = 0;
				//Find index of child
			  while(strcmp(currentLine[i], n[j].name) != 0){
					j++;
				}
				n[k].children[i-2] = n[j].id;
				n[k].num_children++;
				//Uncomment this printf to test that the nodes have the correct children
				//printf("Node %d has a child with id %d\n", k, n[k].children[i-2]);
			}
		}
	}
}

/*
//TODO: MAKE THIS DO SOMETHING
bool checkFirstLineFormat(char*** currentLine){
	return 1;
}
*/

/**Function : execNodes
 * Arguments: 'n' - Pointer to Nodes to be allocated by parsing
 * About execNodes: parseInputLine is supposed to
 * If the node passed has children, fork and execute them first
 * Please note that processes which are independent of each other
 * can and should be running in a parallel fashion
 * */
void execNodes(node_t *n, int numNodes){

	//SPAWN PROCESS TREE

	int indexOfWhoWon = 0;
	for(indexOfWhoWon = 0; indexOfWhoWon < numNodes; indexOfWhoWon++){
		if(strcmp(n[indexOfWhoWon].name, "Who_Won") == 0){
			break;
		}
	}

	if(strcmp(n[indexOfWhoWon].name, "Who_Won") != 0){
		fprintf(stderr, "ERROR: Who_Won not found!\n");
		exit(1);
	}

	node_t currentNode = n[indexOfWhoWon];
	if(currentNode.num_children == 0){
		fprintf(stderr, "ERROR: Who_Won has no children!\n");
		exit(1);
	}

	int numberOfChildren = currentNode.num_children;
	for(int i = 0; i < numberOfChildren; i++){
		//printf("%s, %d\n", currentNode.name, i);
		currentNode.pid = fork();
		if(currentNode.pid == 0){
			currentNode = n[currentNode.children[i]];
			//printf("%s\n", currentNode.name);
			i = -1;
			numberOfChildren = currentNode.num_children;
			//printf("Number of children %d", numberOfChildren);
		}
	}

	if(currentNode.pid == 0){
		//This means it's a leaf so exec the appropriate program
		char* name = currentNode.name;
		strcpy(currentNode.output, "output_");
		strcat(currentNode.output, name);
		char tempOutput[1024];
		strcpy(tempOutput, currentNode.output);
		//printf("node %s has output name %s\n", name, currentNode.output);

		char** args = malloc(sizeof(char*) * (5 + numCandidates));
		args[0] = "leafcounter";
		args[1] = name;
		args[2] = tempOutput;
		args[3] = strnumCandidates;
		for(int i = 4; i < 4 + numCandidates; i++){
			args[i] = candidates[i - 3];
		}
			args[numCandidates + 4] = NULL;
			chmod("./leafcounter", 0700);
			execv("leafcounter", args);
			fprintf(stderr, "ERROR: leafcounter failed to execute on %s\n",
				currentNode.name);
			exit(1);
		}

		//This means it's a parent.
		else {
			pid_t wpid;
			int status = 0;

			//Wait for all children to finish.
			while ((wpid = wait(&status)) > 0);

			//Checks if the node is the root of the entire tree
			//TODO: Check for node with name "Who_won" instead of id = 0

			if(strcmp(currentNode.name, "Who_Won") == 0){
				//exec winner program

				//1. number of input files,
				//2. list of input file names,
				//3. outputfile name
				//4. Number of candidates (str format)
				//5. names of candidates

				//Fetch the children and set their output names to output_ + name
				node_t* children = malloc(sizeof(node_t) * currentNode.num_children);
				for(int i = 0; i < currentNode.num_children; i++){
					children[i] = n[currentNode.children[i]];
					char* name = children[i].name;
					strcpy(children[i].output, "output_");
					strcat(children[i].output, name);
					//printf("file %d is %s with output name %s\n", i, children[i].name, children[i].output);
				}

				//The number of input files is num_children. Need to convert to a str.
				char* str_num_children = malloc(sizeof(char) * 2);
				sprintf(str_num_children, "%d", currentNode.num_children);

				//outputfile name is output_ + currentNode.name
				char* name = currentNode.name;
				strcpy(currentNode.output, "Output_");
				strcat(currentNode.output, name);

				//Number of candidates is given by strnumCandidates

				//Names of candidates is given by candidates (num of candidates is saved too)

				//Now must create an arg array and fill it.
				char** args = malloc(sizeof(char*)*(1+1+currentNode.num_children+1+1+numCandidates+1));
				args[0] = "find_winner";
				args[1] = str_num_children;
				int midArgIndex = 2;
				for(midArgIndex = 2; midArgIndex < 2 + currentNode.num_children; midArgIndex++){
					args[midArgIndex] = children[midArgIndex - 2].output;
				}
				args[midArgIndex] = currentNode.output;
				args[midArgIndex + 1] = strnumCandidates;
				for(int i = midArgIndex + 2; i < midArgIndex + 2 + numCandidates; i++){
					args[i] = candidates[i - midArgIndex - 1];
				}

				//Not sure this is necessary, but set the last argument to NULL
				args[midArgIndex + 2 + numCandidates + 1] = NULL;
				//chmod to get access to the file
				chmod("./find_winner", 0700);

				//Execute the program
				execv("find_winner", args);
				fprintf(stderr, "ERROR: find_winner failed to execute\n");
				exit(1);


			} else {
				node_t* children = malloc(sizeof(node_t) * currentNode.num_children);
				for(int i = 0; i < currentNode.num_children; i++){
					children[i] = n[currentNode.children[i]];
					char* name = children[i].name;
					strcpy(children[i].output, "output_");
					strcat(children[i].output, name);
					//printf("file %d is %s with output name %s\n", i, children[i].name, children[i].output);
				}
				/*
				char*** filesToAggregate[currentNode.num_children][1024];
				for(int i = 0; i < currentNode.num_children; i++){
					children[i] = n[currentNode.children[i]];
					strcpy(filesToAggregate[i], children[i].output);
					//filesToAggregate[i] = children[i].output;

				}*/

				char* name = currentNode.name;
				strcpy(currentNode.output, "output_");
				strcat(currentNode.output, name);
				char* numAggArgs = malloc(sizeof(char)*4);
				sprintf(numAggArgs, "%d", currentNode.num_children);
				char** names = malloc(sizeof(char*) * currentNode.num_children);
				char** args = malloc(sizeof(char*) * (5 + currentNode.num_children + numCandidates));

				//Fill the arg array
				args[0] = "aggregate_votes";
				args[1] = numAggArgs;
				int midArgIndex = 2;
				for(midArgIndex = 2; midArgIndex < 2 + currentNode.num_children; midArgIndex++){
					args[midArgIndex] = children[midArgIndex - 2].output;
				}
				args[midArgIndex] = currentNode.output;
				args[midArgIndex + 1] = strnumCandidates;
				for(int i = midArgIndex + 2; i < midArgIndex + 2 + numCandidates; i++){
					args[i] = candidates[i - midArgIndex - 1];
				}

				//Not sure this is necessary, but set the last argument to NULL
				args[midArgIndex + 2 + numCandidates + 1] = NULL;
				//chmod to get access to the file
				chmod("./aggregate_votes", 0700);

				//Execute the program
				execv("aggregate_votes", args);
				fprintf(stderr, "ERROR: aggregate_votes failed to execute on %s\n",
					currentNode.name);
				exit(1);
			}
			//If it is, then call who won
			//Otherwise call aggregate_votes
	}
}


int main(int argc, char **argv){

	//Allocate space for MAX_NODES to node pointer
	struct node_t* mainnodes=(node_t*)malloc(sizeof(node_t)*MAX_NODES);

	if (argc != 2){
		printf("Usage: %s Program\n", argv[0]);
		return -1;
	}

	//call parseInput
	int num = parseInput(argv[1], mainnodes);


	//Call execNodes on the root node


	return 0;
}
