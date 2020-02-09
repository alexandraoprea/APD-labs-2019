#include<string.h>
#include<stdio.h>
#include<time.h>
#include<math.h>
#include<pthread.h>
#include<stdlib.h>

/**
 * @author cristian.chilipirea
 * 
 */

int n = 1024*1024*100;

int a = 10000000;

int P;

void* threadFunction(void *var)
{
	int thread_id = *(int*)var;

	int start = thread_id * (n/P);
	int stop = (thread_id + 1) *(n/P);
	int i ;

	int c;
	for(int i = start; i <= stop; i++) {
		c = sqrt(a);
	}
}

int main(int argc, char * argv[]) {
	
	int i, j;
	
	P = atoi(argv[1]);
	
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
