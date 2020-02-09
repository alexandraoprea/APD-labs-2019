#include<mpi.h>
#include<stdio.h>
#include<stdlib.h>
#include<math.h>

/**
 * @author cristian.chilipirea
 *
 */

int main(int argc, char * argv[]) 
{
	int rank;
	int nProcesses;
	MPI_Init(&argc, &argv);

	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &nProcesses);
	printf("Hello from %i/%i\n", rank, nProcesses);

	int recv_value;
	int x;
	float *a;

	if(rank==0) { // This code is run by a single process
		int polynomialSize;
		int n;
		int i;
		int j;

		FILE * polFunctionFile = fopen("a1.txt","rt");
		fscanf(polFunctionFile, "%i", &polynomialSize);
		a = malloc(sizeof(float)*polynomialSize);
		for(i=0;i<polynomialSize;i++) {
			fscanf(polFunctionFile, "%f", a+i);
		}
		fclose(polFunctionFile);

		for(int i = 1; i < nProcesses; i++) {
			MPI_Send(&polynomialSize, 1 , MPI_INT, i, 0, MPI_COMM_WORLD);
			MPI_Send(a, polynomialSize, MPI_INT, i, 0, MPI_COMM_WORLD);
		}

	}

	else {
		MPI_Recv(&recv_value, 1 , MPI_INT, 0, MPI_ANY_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		a = malloc(sizeof(float) * recv_value);
		MPI_Recv(a, recv_value, MPI_INT, 0, MPI_ANY_TAG , MPI_COMM_WORLD, MPI_STATUS_IGNORE);
	}

	int sum[3];
	for(x = 0; x < 3; x += 1) {
		float xPowI = pow(x,  rank);
		sum[x] = xPowI * a[rank];
	}

	if(rank == 0) {
		for (int i = 1; i < nProcesses; i++) {
			for(x = 0; x < 3; x += 1) {
				MPI_Recv(&recv_value, 1 , MPI_INT, i, MPI_ANY_TAG , MPI_COMM_WORLD, MPI_STATUS_IGNORE);
				sum[x] += recv_value;
			}
		}
	}

	else {
		for(x = 0; x < 3; x += 1) {
			MPI_Send(&sum[x], 1 , MPI_INT, 0, 0 , MPI_COMM_WORLD);
		}
	}

	if(rank == 0) {
		for (x = 0 ; x < 3 ; x++) {
			printf("Suma pentru %d este %d\n", x, sum[x]);
		}
	}

	MPI_Finalize();

	return 0;
}
