#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>
#include <limits.h>

void* threadFunction(void *var)
{
	long long res;
	int i, j, k;

	for(i = 0; i < 10000; i++) {
		for(j = 0; j < 10000; j++) {
			for(k = 0; k < 10000; k++) {
				res = sqrt(LLONG_MAX); 
			}
		}
	}
}

int main(int argc, char **argv)
{
	int P = 4;
	int i;

	pthread_t tid[P];
	int thread_id[P];
	for(i = 0;i < P; i++)
		thread_id[i] = i;

	for(i = 0; i < P; i++) {
		pthread_create(&(tid[i]), NULL, threadFunction, &(thread_id[i]));
	}

	for(i = 0; i < P; i++) {
		pthread_join(tid[i], NULL);
	}

	return 0;
}
