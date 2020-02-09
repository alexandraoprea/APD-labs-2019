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

    srand(time(NULL) + rank);
    int number;


    if(rank == 0) {
	number = rand() % 100; 
    }
	
    printf("Before Bcast, process %d has number %d\n", rank, number);

    MPI_Bcast(&number, 1, MPI_INT, 0, MPI_COMM_WORLD);

    printf("After Bcast, process %d has number %d\n", rank, number);
     
    MPI_Finalize();

    return 0;

}
