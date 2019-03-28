CC=gcc -std=c99

make: Leaf_Counter Aggregate_Votes Vote_Counter

Leaf_Counter: Leaf_Counter.c util.h
	$(CC) -o Leaf_Counter Leaf_Counter.c util.h

Aggregate_Votes: Aggregate_Votes.c util.h
	$(CC) -o Aggregate_Votes Aggregate_Votes.c util.h

Vote_Counter: Vote_Counter.c util.h
	$(CC) -o Vote_Counter Vote_Counter.c util.h

clean:
	rm $(objects)Leaf_Counter Aggregate_Votes Vote_Counter
