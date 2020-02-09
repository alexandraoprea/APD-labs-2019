compile: helloWorld.c
	gcc -o helloWorld helloWorld.c -lm -O3 -lpthread
	gcc -o useAllCores useAllCores.c -lm -lpthread
	gcc -o addVectors addVectors.c -lm -lpthread
	gcc -o concurrent concurrent.c -lm -lpthread
	gcc -o barrier barrier.c -lm -lpthread

clean:
	rm -f helloWorld
	rm -f useAllCore
	rm -f addVectors
	rm -f concurrent
	rm -f barrier
