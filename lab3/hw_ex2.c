#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>
#include <unistd.h>

pthread_barrier_t b1, b2;
int a;

void* get12(void* arg) {
	
	pthread_barrier_wait(&b1);
	
	a = 5;
	a += 7;

	pthread_barrier_wait(&b2);

	return NULL;
}

void* get5(void* arg)
{
	a = 3;

	pthread_barrier_wait(&b1);
	pthread_barrier_wait(&b2);

	a += 2;

	return NULL;
}

int main(void)
{
	int P = 2;	
	pthread_t tid[P];

	pthread_barrier_init(&b1, NULL, 2);
	pthread_barrier_init(&b2, NULL, 2);

	pthread_create(&tid[0], NULL, get12, NULL);
	pthread_create(&tid[1], NULL, get5, NULL);

	pthread_join(tid[0], NULL);
	pthread_join(tid[1], NULL);

	printf("%d\n", a);

	return 0;
}
