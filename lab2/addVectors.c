#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>

int NReps;
int printLevel;
int N;
int P;
int* a;
int* b;
int* c;

void getArgs(int argc, char **argv)
{
	if(argc < 5) {
		printf("Not enough paramters: ./program N NReps P printLevel\nprintLevel: 0=no, 1=some, 2=verbouse\n");
		exit(1);
	}

	N = atoi(argv[1]);
	NReps = atoi(argv[2]);
	P = atoi(argv[3]);
	printLevel = atoi(argv[4]);
}

void init()
{
	a = malloc(sizeof(int) * N);
	b = malloc(sizeof(int) * N);
	c = malloc(sizeof(int) * N);

	if(a == NULL || b == NULL || c == NULL) {
		printf("malloc failed!");
		exit(1);
	}

	int i;
	for(i = 0; i < N; i++) {
		a[i] = i%500;
		b[i] = i%500;
	}
}

void printPartial()
{
	int i;
	for(i = 0; i < 10; i++)
		printf("%i ", c[i]);

	printf("\n");

	for(i = 20; i < N; i+=N/10)
		printf("%i ", c[i]);

	printf("\n");

	for(i = N - 10; i < N; i++)
		printf("%i ", c[i]);

	printf("\n");
}

void printAll()
{
	int i;
	for(i = 0; i < N; i++)
		printf("%i ", c[i]);
	printf("\n");
}

void print()
{
	if(printLevel == 0) {
		return;
	}
	else if(printLevel == 1) {
		printPartial();
	}
	else {
		printAll();
	}
}

int getMin(int x, int y) {
	if(x < y) {
		return x;
	}
	return y;
}

void *threadFunction(void* var) {
	int tid = *(int*) var;
	int i, j;

	int start = tid * ceil((double)N/P);
	int end = getMin(N, (tid + 1)*ceil((double)N/P));

	for(j = 0; j < NReps; j++) {
		for(i = start; i < end; i++) {
			c[i] = a[i] + b[i];
		}
	}
}

int main(int argc, char *argv[])
{
	int i;
	getArgs(argc, argv);
	init();
	
	pthread_t tid[P];
	int thread_id[P];
	for(i = 0; i < P; i++)
		thread_id[i] = i;

	for(i = 0; i < P; i++) {
		pthread_create(&(tid[i]), NULL, threadFunction, &(thread_id[i]));
	}
	
	
	for(i = 0; i < P; i++) {
		pthread_join(tid[i], NULL);
	}

	print();

	return 0;
}
