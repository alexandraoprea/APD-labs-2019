#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define  MASTER		0

int main (int argc, char *argv[])
{
    int   numtasks, rank, len;
    char hostname[MPI_MAX_PROCESSOR_NAME];

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &numtasks);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Get_processor_name(hostname, &len);

    int v[numtasks];
    int recv_value;

    if(rank == 0) {
        for (int i = 0; i < numtasks ; i++) {
            v[i] = i + 1;
        }
        for (int i = 1 ; i < numtasks; i++) {
            MPI_Send( &v[i], 1 , MPI_INT, i, 0 , MPI_COMM_WORLD);
        }
    }
    else {
        MPI_Recv( &recv_value, 1 , MPI_INT, 0, MPI_ANY_TAG , MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    }

    int sum = recv_value;
    if ( rank == 0) {
        sum = v[0];
    }
    int pas = 1;
    if(rank % 2 == 1) {
        MPI_Recv( &recv_value, 1 , MPI_INT, rank - pas, MPI_ANY_TAG , MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        sum += recv_value;
    }
    else {
        MPI_Send( &sum, 1 , MPI_INT, rank + pas, 0 , MPI_COMM_WORLD);
    }
    pas++;

    while(pas <= (ceil(log2(numtasks)))){
        int power = pow(2, pas - 1);
        if(rank % power == (power - 1) ) {
            int newrank;
            newrank = rank / power;
            if(newrank % 2 == 1) {
                 MPI_Recv( &recv_value, 1 , MPI_INT, rank - power, MPI_ANY_TAG , MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                 sum += recv_value;
            }
            else {
                 MPI_Send( &sum, 1 , MPI_INT, rank + power, 0 , MPI_COMM_WORLD);
            }
        }
        pas++;
    }
    
    if(rank == (numtasks - 1)) {
        printf("%d", sum);
    }
   
    MPI_Finalize();
}