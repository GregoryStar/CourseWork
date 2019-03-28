all : main.o Duck.o DecoyDuck.o MallardDuck.o MuteQuack.o Quack.o RubberDuck.o Squeak.o QuackBehavior.o
	g++ main.o Duck.o DecoyDuck.o MallardDuck.o MuteQuack.o Quack.o RubberDuck.o Squeak.o QuackBehavior.o -o lab03.out

main.o : main.cpp
	g++ -c main.cpp -o main.o

Duck.o : Duck.cpp
	g++ -c Duck.cpp -o Duck.o

DecoyDuck.o : DecoyDuck.cpp
	g++ -c DecoyDuck.cpp -o DecoyDuck.o

MallardDuck.o : MallardDuck.cpp
	g++ -c MallardDuck.cpp -o MallardDuck.o

MuteQuack.o : MuteQuack.cpp
	g++ -c MuteQuack.cpp -o MuteQuack.o

Quack.o : Quack.cpp
	g++ -c Quack.cpp -o Quack.o

RubberDuck.o : RubberDuck.cpp
	g++ -c RubberDuck.cpp -o RubberDuck.o 

QuackBehavior.o : QuackBehavior.cpp
	g++ -c QuackBehavior.cpp -o QuackBehavior.o

Squeak.o : Squeak.cpp
	g++ -c Squeak.cpp -o Squeak.o 

clean :
	rm *.o *.out
