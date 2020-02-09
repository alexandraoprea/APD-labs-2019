#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>
#include <unistd.h>

void* one(void* var) {
	
	pthread_barrier_t* barrier = (pthread_barrier_t*)var;
	
	printf("1 ");

	printf("\n");

	pthread_barrier_wait(barrier);
}

void* two(void* var) {
	
	pthread_barrier_t* barrier = (pthread_barrier_t*)var;

	pthread_barrier_wait(barrier);

	printf("2 ");
	
	printf("\n");
}

int main(int argc, char **argv)
{
	int i, P = 2;
	pthread_t tid[P];
	pthread_barrier_t barrier;

	pthread_barrier_init(&barrier, NULL, 2);

	pthread_create(&tid[0], NULL, one, &barrier);
	pthread_create(&tid[1], NULL, two, &barrier);

	for(i = 0; i < 2; i++)
	{
		pthread_join(tid[i], NULL);
	}

	return 0;
}
