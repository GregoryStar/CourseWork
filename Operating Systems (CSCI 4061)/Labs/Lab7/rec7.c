#define _BSD_SOURCE
#define NUM_ARGS 2

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <dirent.h>
#include <string.h>
#include <time.h>

struct matrix {

	int x;
	int y;
	int** data;
};

struct matrix* newMatrix(int x, int y) {

	int** data = malloc(sizeof(int*) * x);
	for(int i = 0; i < x; i++){
		data[i] = (int*)malloc(sizeof(int) * y);
	}
	struct matrix* m = malloc(sizeof(struct matrix));
	m->x = x;
	m->y = y;
	m->data = data;
	return m;
}

void diagAdd(struct matrix* m, int c) {

	int d = (rand() % m->y);
	for (int i=0; d+i < m->y; ++i) {
		m->data[i][d+i] += c;
	}
}

matrixMultiply(struct matrix** matrices, int start, int end, struct matrix* mat) {
	for (int i=start+1; i < end; ++i) {
		for (int j=0; j < matrices[i]->x; ++j) {
			for (int k=0; k < matrices[i]->y; ++k) {
				for (int l=0; l < matrices[i]->x; ++l) {
					mat->data[j][k] += mat->data[j][l] * matrices[i]->data[l][k];
				}
			}
		}
	}
}

int main(int argc, char** argv) {

	if (argc < NUM_ARGS + 1) {

		printf("Wrong number of args, expected %d, given %d\n", NUM_ARGS, argc - 1);
		exit(1);
	}

	int max = atoi(argv[1]);
	int duration = atoi(argv[2]);
	int start = time(NULL);

	srand(time(NULL));

	while (time(NULL) < start + duration) {

		struct matrix** matrices = malloc(sizeof(struct matrix*) * max);
		for(int i = 0; i < max; ++i){
			matrices[i] = (struct matrix*)malloc(sizeof(struct matrix));
		}

		for (int i=0; i < max; ++i) {

			// Initialize the matrices.
			matrices[i] = newMatrix(256, 256);
			for (int j=0; j < 10; ++j) diagAdd(matrices[i], (int)(rand() % 256));
		}

		struct matrix* m = malloc(sizeof(struct matrix));
		m->x = matrices[0]->x;
		m->y = matrices[0]->y;
		m->data = matrices[0]->data;


		matrixMultiply(matrices, 0, max, m);

		printf("First element in matrix = %d\n", m->data[0][0]);
		for(int i = 0; i < max; ++i){
			for(int j = 0; j < matrices[i]->x; ++j){
				free(matrices[i]->data[j]);
			}
			free(matrices[i]->data);
			free(matrices[i]);
		}
		free(matrices);
		free(m);
	}
}
