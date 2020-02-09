#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>

#define min(x, y) (((x) < (y)) ? (x) : (y))

int NReps;
int printLevel;
int N;
int** a;
int P;
pthread_barrier_t barrier;

void getArgs(int argc, char **argv)
{
	if(argc < 4) {
		printf("Not enough paramters: ./program N NReps printLevel P\nprintLevel: 0=no, 1=some, 2=verbouse\n");
		exit(1);
	}
	N = atoi(argv[1]);
	NReps = atoi(argv[2]);
	printLevel = atoi(argv[3]);
    P = atoi(argv[4]);
}

void init()
{
	a = malloc(sizeof(int *) * N);
	if(a == NULL) {
		printf("malloc failed!");
		exit(1);
	}

	int i, j;
	for(i = 0; i < N; i++) {
		a[i] = malloc(sizeof(int) * N);
		if(a[i] == NULL) {
			printf("malloc failed!");
			exit(1);
		}
	}

	for(i = 0; i < N; i++) {
		for(j = 0; j < N; j++) {
			a[i][j] = rand()%N;
		}
	}
}

void printAll()
{
	int i, j;
	for(i = 0; i < N; i++) {
		for(j = 0; j < N; j++) {
			printf("%i\t",a[i][j]);
		}
		printf("\n");
	}
}

void printPartial()
{
	printAll();
}

void print()
{
	if(printLevel == 0)
		return;
	else if(printLevel == 1)
		printPartial();
	else
		printAll();
}

int compareASC (const void *x, const void *y)
{
  return (*(int *)x - *(int *)y);
}

int compareDESC (const void *x, const void *y)
{
  return (*(int *)y - *(int *)x);
}

void rowSort (int rows, int columns, int rowindex, int **matrix, int (*compar)(const void*,const void*)) 
{
	qsort (matrix[rowindex], columns, sizeof (int), compar);
}

void columnSort (int rows, int columns, int columnindex, int **matrix, int (*compar)(const void*,const void*)) 
{
  int aux[rows];
    for (int i = 0; i < rows; ++i)
        aux[i] = matrix[i][columnindex];
    

    qsort(aux, rows, sizeof (int), compar);

    for (int i = 0; i < rows; ++i) {
        matrix[i][columnindex] = aux[i];
    }
}

void *threadFunction (void *var) {
    int thread_id = *(int *) var;

	int start = thread_id * ceil((double) N / (double) P);
	int end = min (N, ceil ((double) N / (double) P) * (thread_id + 1));

    for (int k = 0; k < log2(N); k++) {
		
		for (int i = start; i < end; ++i) {
			if (i % 2 == 0)
				rowSort (N,N, i, a, compareASC);
			else
				rowSort (N,N, i, a, compareDESC);
		}

        pthread_barrier_wait(&barrier);

		for (int i = start; i < end; ++i) {
			columnSort (N,N, i, a, compareASC);
		}

        pthread_barrier_wait(&barrier);
	}

}

int main(int argc, char *argv[])
{
	int i, j, k;
	getArgs(argc, argv);
	init();
	printAll();
	printf("\n");
    pthread_barrier_init(&barrier, NULL, P);
    pthread_t threads[P];
    int threads_id[P];
    for (int i = 0; i < P; ++i)
        threads_id[i] = i;
    for (int i = 0; i < P; ++i)
        pthread_create(&threads[i], NULL, threadFunction, &threads_id[i]);
    for (int i = 0; i < P; ++i)
        pthread_join(threads[i], NULL);

    pthread_barrier_destroy(&barrier);
	
	print();

	return 0;
}