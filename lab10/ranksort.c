#include<mpi.h>
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#define N 10000

/**
 * @author cristian.chilipirea
 *
 */

void compareVectors(int * a, int * b) {
	// DO NOT MODIFY
	int i;
	for(i = 0; i < N; i++) {
		if(a[i]!=b[i]) {
			printf("Sorted incorrectly\n");
			return;
		}
	}
	printf("Sorted correctly\n");
}

void displayVector(int * v) {
	// DO NOT MODIFY
	int i;
	int displayWidth = 2 + log10(v[N-1]);
	for(i = 0; i < N; i++) {
		printf("%*i", displayWidth, v[i]);
	}
	printf("\n");
}

int cmp(const void *a, const void *b) {
	// DO NOT MODIFY
	int A = *(int*)a;
	int B = *(int*)b;
	return A-B;
}
 
int main(int argc, char * argv[]) {
	int rank;
	int nProcesses;
	MPI_Init(&argc, &argv);

	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &nProcesses);
	printf("Hello from %i/%i\n", rank, nProcesses);

	int *v = (int*)malloc(sizeof(int)*N);
	int *vQSort;
	int *result;
	int start;
	int end;

	start = rank * ceil((double) N / nProcesses);

	if(N < (rank + 1) * ceil((double) N / nProcesses)){
		end = N;
	}
	else {
		end = (rank + 1) * ceil((double) N / nProcesses);
	}

	if(rank==0) { // This code is run by a single process
		int sorted = 0;
		int aux;
		vQSort = (int*)malloc(sizeof(int)*N);
		int i;

		// generate the vector v with random values
		// DO NOT MODIFY
		srand(42);
		for(i = 0; i < N; i++) {
			v[i] = rand()%N;
		}
		result = (int*)malloc(sizeof(int) * N);
		// make copy to check it against qsort
		// DO NOT MODIFY
		for(i = 0; i < N; i++)
			vQSort[i] = v[i];
		qsort(vQSort, N, sizeof(int), cmp);

		
	}
	else {
		result = calloc(end - start, sizeof(int));
	}

	MPI_Bcast(v, N, MPI_INT, 0, MPI_COMM_WORLD);
	
	for (int j = start; j < end; j++) {
		for (int i = 0; i < N; i++) {
			if (v[j] > v[i] || (i < j && v[j] == v[i])) {
				result[j - start]++;
			}	
		}
	}

	MPI_Gather(result, end - start, MPI_INT, result, end - start, MPI_INT, 0, MPI_COMM_WORLD);
		
	if(rank == 0) {
		int *aux = (int*) malloc(sizeof(int) * N);
		for(int i = 0; i < N; i++) {
			aux[result[i]] = v[i];
		}
		compareVectors(aux, vQSort);
		free(aux);
	}

	free(result);
	free(vQSort);

	MPI_Finalize();
	return 0;
}
