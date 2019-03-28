#include <stdlib.h>
#include <stdio.h>

struct bankAccount {

	char * name;
	double balance;
};

// Returns a pointer that points to the value of val.
int* getInt(int val) {
	int* p = malloc(sizeof(int));
	*p = val;
	return p;
}

int main() {

	// Pointer review. You MUST use getInt(int) (you may alter the function though).
	int* num = getInt(5);
	printf("Value of x = %d\n", *num);

	// Create an array of 100 integers.
	int* array = malloc(sizeof(int) * 100);

	// Create a two-dimensional array of size 10x25.
	int x = 10;
	int y = 25;
	int* twoDim = (int*)malloc(sizeof(int) * x * y);
	for (int i=0; i < x; i++) {
		//twoDim[i] = malloc(sizeof(int*) * y);
		for (int j=0; j < y; j++) {
			*(twoDim + i*x + j) = i * j;
		}
	}
	printf("Element at location (5,5) = %d\n", *(twoDim + 5*x + 5));

	// Structure review. The print statement must use a struct pointer.
	struct bankAccount acc1 = {"My Account", 1000};
	struct bankAccount* p = &acc1;
	printf("Balance in the account %s = %f\n", (*p).name, (*p).balance);
}
