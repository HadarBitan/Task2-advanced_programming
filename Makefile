.PHONY: all
all: generator primeCounter myPrimeCounter

generator:  generator.c
	gcc -o randomGenerator generator.c 

primeCounter:	primeCounter.c
	gcc -o primeCounter primeCounter.c

myPrimeCounter:  myPrimeCounter.c queue.h
	gcc -o myPrimeCounter myPrimeCounter.c queue.c -pthread 


.PHONY: clean
clean:
	-rm randomGenerator primeCounter 2>/dev/null
