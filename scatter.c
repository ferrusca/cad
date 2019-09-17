/** 
  * Assume the following toy problem: 
  you want to scatter the array [1 2 3 4 5 6] to two processes. 
  Proc0 should have the [1 2 3] part and the Proc1 should have the [4 5 6] part. 
  * In this case, the global array has size 6 and the local arrays have size 3. 
  * The Proc0 gets the global elements 0, 1, 2 and assigns them to its local 0, 1, 2. 
  * The Proc1 gets the global elements 3, 4, 5 and assigns them to its local 0, 1, 2.
  * MPI_Scatterv which doesn't assume the same number of local elements for every process.
  *
  */

#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    int size, rank;

    MPI_Status status; 

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int globaldata[4];

    int i;
    if (rank == 0) {
        for (i=0; i<size; i++) {
          globaldata[i] = i;
        }
        printf("1. Processor %d has data: ", rank);
        for (i=0; i<size; i++) {
          printf("%d ", globaldata[i]);
        }
        printf("\n");
    }

    // sendbuf
    // address of send buffer (choice, significant only at root)
    // sendcount
    // number of elements sent to each process (integer, significant only at root)
    // sendtype
    // data type of send buffer elements (significant only at root) (handle)
    // recvbuf
    //address of receive buffer (choice)
    // recvcount
    // number of elements in receive buffer (integer)
    // recvtype
    // data type of receive buffer elements (handle)
    // root
    // rank of sending process (integer)
    // comm
    // communicator (handle)
    int localdata[1]; 

    MPI_Scatter(globaldata, 1, MPI_INT, &localdata, 1, MPI_INT, 0, MPI_COMM_WORLD);

    printf("2. Processor %d has data %d\n", rank, localdata);
    localdata[0]= 5;
    int localdataAgain = localdata[0];
    printf("3. Processor %d now has %d\n", rank, localdata);

    MPI_Gather(&localdataAgain, 1, MPI_INT, globaldata, 1, MPI_INT, 0, MPI_COMM_WORLD);

    if (rank == 0) {
      printf("4. Processor %d has data: ", rank);
      for (i=0; i<size; i++) {
        printf("%d ", globaldata[i]);
      }
      printf("\n");
    }

    MPI_Finalize();
    return 0;
}