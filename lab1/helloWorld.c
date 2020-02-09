#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>
#include <unistd.h>

void* threadFunction(void *var)
{
	int thread_id = *(int*)var;
	
	int i;
	for(i = 0; i < 25; i++) {
		printf("Hello world from thread %i, the current index is %d\n", thread_id, i);
	}
	
	//printf("Hello world from thread %i\n", thread_id);
}

void* threadFunction2(void *var)
{	
	int thread_id = *(int*)var;
	
	int i;
	for(i = 0; i < 25; i++) {
		printf("Hello world from thread %i, the current index is %d\n", thread_id, i);
	}

	//printf("Hello world from thread %i\n", thread_id);
}

int main(int argc, char **argv)
{
	//int P = 10;	
	int P = sysconf(_SC_NPROCESSORS_ONLN);
	int i;

	pthread_t tid[P];
	int thread_id[P];
	for(i = 0; i < P; i++)
		thread_id[i] = i;

	/*
	for(i = 0; i < P; i++) {
		pthread_create(&(tid[i]), NULL, threadFunction, &(thread_id[i]));
	}
	*/
	
	pthread_create(&(tid[0]), NULL, threadFunction, &(thread_id[0]));
	pthread_create(&(tid[1]), NULL, threadFunction2, &(thread_id[1]));
	
	
	for(i = 0; i < 2; i++) {
		pthread_join(tid[i], NULL);
	}
	
	/*
	for(i = 0; i < P; i++) {
		pthread_join(tid[i], NULL);
	}
	*/

	//afiseaza numarul de core-uri
	//din linie de comanda se poate folosi comanda nproc
	printf("Number of cores is: %ld\n", sysconf(_SC_NPROCESSORS_ONLN));
	
	return 0;
}
