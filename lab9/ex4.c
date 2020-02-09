#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc,char* argv[]) {

    int rank;
    int nProcesses;
    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &nProcesses);

    int v[12];
    int numbers[3];

    if(rank == 0) {
	for(int i = 0; i < 12; i++) {
		v[i] = i;
	}
    }  

    MPI_Scatter(&v, 3, MPI_INT, &numbers, 3, MPI_INT, 0, MPI_COMM_WORLD);
    for(int i = 0; i < 3; i++) {
        numbers[i] += rank;
    }
    MPI_Gather(&numbers, 3, MPI_INT, &v, 3, MPI_INT, 0, MPI_COMM_WORLD);

    if(rank == 0) {
	for(int i = 0; i < 12; i++) {
		printf("%d ", v[i]);
	}
	printf("\n");
    }  

    MPI_Finalize();

    return 0;

}
