#include<mpi.h>
#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include<string.h>

/**
 * @author cristian.chilipirea
 * Run: mpirun -np 2 ./a.out
 */

int main(int argc, char * argv[])
{
    srand(time(NULL));

    int* v = malloc(10 * sizeof(*v));
    int i, rank, nProcesses;
    MPI_Status stat;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &nProcesses);

    memset(v, 0, 10 * sizeof(*v));

    if (rank == 0) {
        for (i = 0; i != 10; ++i) {
            v[i] = i;
        }

        MPI_Send(v, 10, MPI_INT, 1, MPI_TAG_UB, MPI_COMM_WORLD);
        printf("Got here! MPI_Send is non-blocking because there is no one to do a receive.\n");
    } else {
        MPI_Recv(v, 10, MPI_INT, 0, MPI_ANY_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        printf("Received: ");

        for (i = 0; i != 10; ++i) {
            printf("%d ", v[i]);
        }

        printf("\n");
    }

    MPI_Finalize();

    return 0;
}
