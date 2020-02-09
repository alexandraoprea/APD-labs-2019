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
    int next;
	
 
       if(rank == 0) {
		next = rank + 1;
  		int number = rand() % 100;
		MPI_Send(&number, 1, MPI_INT, next, 0, MPI_COMM_WORLD);
		//next = nProcesses - 1;
		//MPI_Recv(&number, 1, MPI_INT, next, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		printf("%d\n", number);
	}
	else if(rank == nProcesses - 1) {
		next = rank - 1;
		MPI_Recv(&number, 1, MPI_INT, next, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		printf("%d\n", number);
		next = 0;
		MPI_Send(&number, 1, MPI_INT, next, 0, MPI_COMM_WORLD);
	}
	else {
		next = rank - 1;
		MPI_Recv(&number, 1, MPI_INT, next, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		number += 2;
		printf("%d\n", number);
		next = rank + 1;
		MPI_Send(&number, 1, MPI_INT, next, 0, MPI_COMM_WORLD);
	}


    MPI_Finalize();

    return 0;

}
