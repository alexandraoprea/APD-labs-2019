#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc,char* argv[]) 
{
    int rank;
    int nProcesses;
    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &nProcesses);

    int number;
    
    srand(time(NULL) + rank);

    
 	   
    if(rank == 0) {
	number = rand() % 100;
	MPI_Send(&number, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
        printf("Value %d was sent by the process %d\n", number, rank);
    }
  
    if(rank == 1) {
	MPI_Recv(&number, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf ("Process %d got value %d\n", rank, number);
    }

    
    /*
    int next = (rank + 1) % nProcesses;
    int prev = (rank + nProcesses - 1) % nProcesses;

    if (rank == 0) {
        number = rand() % 100;

        printf("Process 0 sending %d to %d\n",
               number, next);
        MPI_Send(&number, 1, MPI_INT, next, 0, MPI_COMM_WORLD);
        printf("Process 0 sent to %d\n", next);
    }

    while (1) {
        MPI_Recv(&number, 1, MPI_INT, prev, 0, MPI_COMM_WORLD,
                 MPI_STATUS_IGNORE);

        if (rank == 0) {
            number += 2;
            printf("Process %d added 2 to value: %d\n", rank, number);
        }

        MPI_Send(&number, 1, MPI_INT, next, 0, MPI_COMM_WORLD);
        if (number == 1000) {
            printf("Process %d exiting\n", rank);
            break;
        }
    }

    if (rank == 0) {
        MPI_Recv(&number, 1, MPI_INT, prev, 0, MPI_COMM_WORLD,
                 MPI_STATUS_IGNORE);
    }
	

    */

    /*
    for(int i=0; i < nr; i++){
        double x, y;
        x = ((double)rand() / RAND_MAX) * 2 - 1;
        y = ((double)rand() / RAND_MAX) * 2 - 1;
        if(sqrt(x*x + y*y) < 1)
            count++;
    }
    if(rank != 0)
        MPI_Send(&count, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);

    else {
        for(int i=0; i < nProcesses-1; i++){
            MPI_Recv(&tmp, 1, MPI_INT, MPI_ANY_SOURCE,  0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            count += tmp;
        }
        double pi = (4.0 * count) / 1000000;
        printf("%f\n", pi);
    }
    */	
 
    /*if (rank+1 != nProcesses){
        nr = rank + 10;
        MPI_Send(&nr, 1, MPI_INT, 1, nr, MPI_COMM_WORLD);
        MPI_Send(&nr, 1, MPI_INT, 1, nr+1, MPI_COMM_WORLD);
        MPI_Send(&nr, 1, MPI_INT, 1, nr+2, MPI_COMM_WORLD);
    }
    else
    {
        MPI_Status stat;
        for(int i=0; i< 3; i++){
            MPI_Recv(&nr, 1, MPI_INT, 0,  MPI_ANY_TAG, MPI_COMM_WORLD, &stat);
            printf("Venit cu tag-ul %d nr %d\n", stat.MPI_TAG, nr);
        }
    }*/


    /*if (rank+1 != nProcesses){
        nr = rank + 10;
        MPI_Send(&nr, 1, MPI_INT, nProcesses-1, 0, MPI_COMM_WORLD);
    }
    else
    {
        MPI_Status stat;
        for(int i=0; i< nProcesses-1; i++){
            MPI_Recv(&nr, 1, MPI_INT, 0,  0, MPI_COMM_WORLD, &stat);
            printf("Venit de pe procesul %d nr %d\n", stat.MPI_SOURCE, nr);
        }
    }*/
    


    /*if(rank != 0)
        MPI_Recv(&nr, 1, MPI_INT, rank-1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

    nr += 2;
    
    printf("%d\n", nr);

    if(rank+1 == nProcesses)
        MPI_Send(&nr, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
    else
        MPI_Send(&nr, 1, MPI_INT, rank+1, 0, MPI_COMM_WORLD);

    if(rank == 0)
        MPI_Recv(&nr, 1, MPI_INT, nProcesses-1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    */


    /*if (rank == 0) {
        for(int i=0; i < 12; i++)
            number[i] = i;
    }*/
    /*} else {

        //MPI_Recv(&number, 10, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        //printf("Process 1 received number %d from process 0\n", number);
    }*/
    /*for(int i=0; i < 12; i++){
        printf("%d ", number[i]);
    }
    printf("\n");*/

    /*MPI_Scatter(&number, 3, MPI_INT, &numbers, 3, MPI_INT, 0, MPI_COMM_WORLD);
    for(int i=0; i < 3; i++)
        numbers[i] += 42;
    MPI_Gather(&numbers, 3, MPI_INT, &number, 3, MPI_INT, 0, MPI_COMM_WORLD);*/

    /*if (rank == 0) {
        for(int i=0; i < 12; i++){
            printf("%d ", number[i]);
        }
        printf("\n");
    }*/
    MPI_Finalize();
    return 0;
}
