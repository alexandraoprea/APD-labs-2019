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

    int number;
    
    srand(time(NULL) + rank);

    int v[] = {42, 23, 53, 12, 78};
 	   
    if(rank == 0) {
	number = rand() % 100;
	MPI_Send(&v, 5, MPI_INT, 1, 0, MPI_COMM_WORLD);
        //printf("Value %d was sent by the process %d\n", number, rank);

	for(int i = 0; i < 5; i++) {
		printf("%d ", v[i]);
	}


	printf("\n");
    }
  
    if(rank == 1) {
	MPI_Recv(&v, 5, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        //printf ("Process %d got value %d\n", rank, number);

	for(int i = 0; i < 5; i++) {
		printf("%d ", v[i]);
	}

	printf("\n"); 
    }

    MPI_Finalize();
    return 0;

}

