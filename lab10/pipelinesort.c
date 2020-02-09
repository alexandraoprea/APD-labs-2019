#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define N 64

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
	int *vQSort;

	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &nProcesses);
	//printf("Hello from %i/%i\n", rank, nProcesses);

	int *v = (int*)malloc(sizeof(int)*N);
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

		// make copy to check it against qsort
		// DO NOT MODIFY
		for(i = 0; i < N; i++)
			vQSort[i] = v[i];
		qsort(vQSort, N, sizeof(int), cmp);
	}

	int pas = 1;
	int value = -1;

	if(rank == 0) {
		value = v[0];
	}

	int next = 1;
	int recv_value;
	pas++;

	while (pas <= nProcesses) {
		if(rank == 0) {
			if(v[next] < value){
				MPI_Send(&v[next], 1 , MPI_INT, rank + 1, 0 , MPI_COMM_WORLD);
			}
			else {
				MPI_Send(&value, 1 , MPI_INT, rank + 1, 0 , MPI_COMM_WORLD);
				value = v[next];
			}
			next++;
		}

		if(rank < pas && rank != 0) {
			MPI_Recv(&recv_value, 1 , MPI_INT, rank - 1, MPI_ANY_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			if(value == -1) {
				value = recv_value;
			}
			else {
				if(recv_value < value) {
					MPI_Send(&recv_value, 1 , MPI_INT, rank + 1, 0 , MPI_COMM_WORLD);
				}
				else {	
					MPI_Send(&value, 1 , MPI_INT, rank + 1, 0 , MPI_COMM_WORLD);
					value = recv_value;
				}
			}
		}
		pas++;
	}

	printf("value: %d rank: %d\n", value, rank);

	if(rank == 0) {
		compareVectors(v, vQSort);
	}
	
	/*
	if(rank != 0 ) {
		MPI_Send(&value, 1 , MPI_INT, 0, 0 , MPI_COMM_WORLD);
	}
	else {
		for(int i = 1; i < nProcesses; i++){
			MPI_Recv(&v[i], 1 , MPI_INT, i, MPI_ANY_TAG , MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		}
		v[0] = value;
	}

	if(rank == 0) {
		//displayVector(v);
		compareVectors(v, vQSort);
	}
	*/

	free(v);

	MPI_Finalize();

	return 0;
}
