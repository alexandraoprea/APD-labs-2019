#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>
#include <unistd.h>

int a;
pthread_barrier_t b;

void *threadFunction(void* arg) {
    
	int i;

    	for (i = 0; i < 100; ++i) {
        	pthread_barrier_wait(&b);
        	a += 2;
    	}

    	return NULL;
}

int main(int argc, char **argv)
{
    	int i, P = 2;

    	pthread_t tid[P];

    	pthread_barrier_init(&b, NULL, 2);

    	for (i = 0; i < P; i++) {
        	pthread_create(&tid[i], NULL, threadFunction, NULL);
    	}

    	for (i = 0; i < P; i++) {
        	pthread_join(tid[i], NULL);
    	}

    	printf("%d\n", a);

    	pthread_barrier_destroy(&b);

    	return 0;
}

