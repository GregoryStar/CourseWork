CXX = g++
COMP = ${CXX} -c
LINK = ${CXX} -o
ALLOFILES = Customer.o Movie.o main.o

all: lab09.out
Customer.o: Customer.h Customer.cpp
	${COMP} Customer.cpp
Movie.o: Movie.h Movie.cpp
	${COMP} Movie.cpp
main.o: main.cpp
	${COMP} main.cpp
lab09.out: ${ALLOFILES}
	${LINK} lab09.out ${ALLOFILES}
clean:
	rm *.o *.out
