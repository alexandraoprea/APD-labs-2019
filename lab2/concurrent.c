#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>

int NReps;
int P;

int a;
pthread_mutex_t mutex;

void* threadFunction(void *var)
{
	int iters = *(int*)var;
	int i;
	for(i = 0; i < iters; i++) {
		pthread_mutex_lock(&mutex);
		a = a + 2;
		pthread_mutex_unlock(&mutex);
	}
	
	return NULL;
}

void getArgs(int argc, char **argv)
{
	if(argc < 3) {
		printf("Not enough paramters: ./program NReps P\n");
		exit(1);
	}

	NReps = atoi(argv[1]);
	P = atoi(argv[2]);
}

int main(int argc, char **argv)
{
	int i;
	getArgs(argc, argv);

	pthread_t tid[P];
	int thread_id[P], iters[P];
	for(i = 0; i < P; i++)
		thread_id[i] = i;

	 for (i = 0; i < P - 1; i++) {
        	iters[i] = ceil((double)NReps/P);
        	pthread_create(&tid[i], NULL, threadFunction, &iters[i]);
    	}

    	iters[P - 1] = NReps - (P - 1) * ceil((double)NReps / P);
    	pthread_create(&tid[P - 1], NULL, threadFunction, &iters[P - 1]);

	for(i = 0; i < P; i++) {
		pthread_join(tid[i], NULL);
	}
	
	printf("%d\n", a);

	pthread_mutex_destroy(&mutex);

	return 0;
}
