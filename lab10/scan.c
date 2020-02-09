#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define  MASTER	0

int main (int argc, char *argv[])
{
    int n, rank, len;
    char hostname[MPI_MAX_PROCESSOR_NAME];

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &n);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Get_processor_name(hostname, &len);

    int v[n];
    int recv_value;

    if(rank == 0) {
        for(int i = 0; i < n; i++) {
            v[i] = i + 1;
        }
        for (int i = 1; i < n; i++) {
            MPI_Send(&v[i], 1, MPI_INT, i, 0 , MPI_COMM_WORLD);
        }
    }

    else {
        MPI_Recv(&recv_value, 1 , MPI_INT, 0, MPI_ANY_TAG , MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    }

    int sum = recv_value;

    if (rank == 0) {
        sum = v[0];
    }

    int pas = 1;

    while(pas < n) {
        if ((rank + pas) < n) {
            MPI_Send(&sum, 1 , MPI_INT, rank + pas, 0 , MPI_COMM_WORLD);
        }

        if ((rank - pas) >= 0) {
            MPI_Recv(&recv_value, 1, MPI_INT, rank - pas, MPI_ANY_TAG , MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            sum += recv_value;
        }
        pas = 2 * pas;
        MPI_Barrier(MPI_COMM_WORLD);
    }

    printf("rank: %d suma: %d\n", rank, sum);
   
    MPI_Finalize();

    return 0;
}
