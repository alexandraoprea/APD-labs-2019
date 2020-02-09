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
    /**
    int pas = 1;
    int a = 3;
    if (pas == 1 && rank == 0) {
        a = 3;
        MPI_Send( &a, 1 , MPI_INT, 1, 0 , MPI_COMM_WORLD);
    }
    if (pas == 1 && rank == 1){
        MPI_Recv( &a, 1 , MPI_INT, 0, MPI_ANY_TAG , MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    }
    */
    //printf("starting?");

    int a;
    if(rank == 0) {
            a = 3;
    }

    int pas = 1;
  //  printf("%f", ceil(log2(numtasks)));

    while(pas <= (ceil(log2(numtasks)))){
        
        int senders = pow(2, pas - 1) ;
        int receivers = pow(2, pas);
        if(rank < senders) {
            if ((senders + rank) < numtasks) {
                MPI_Send( &a, 1 , MPI_INT, senders + rank, 0 , MPI_COMM_WORLD);
            }
        }
        else {
            if(rank < receivers) {
         //       printf("rank: %d, senders + rank :%d", rank, rank - senders);
                MPI_Recv( &a, 1 , MPI_INT, rank - senders, MPI_ANY_TAG , MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            }
        }
        pas++;
    }
    printf("%d", a);
    
    MPI_Finalize();
}