/**
  *   Tarea 1
  *   Alunno: Ferrusca Ortiz Jorge Luis
  *   Fecha de entrega: 10-septiembre-2019
  */ 

#include <stdio.h>
#include <mpi.h>

int add(int rank, int i_message);

int main(int argc, char**argv){
  int rank, size, tag, i_message_elements = 1;
  int i_message = 0;
  // Communication info structure
  MPI_Status status; 
  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  if (rank == 0) {
    printf("El proceso %d envía i = %d\n", rank, i_message);
    MPI_Send(&i_message, i_message_elements, MPI_INT, 1, tag, MPI_COMM_WORLD);
    MPI_Recv(&i_message, i_message_elements, MPI_INT, size-1, tag, MPI_COMM_WORLD, &status);
    printf("El proceso %d recibió i = %d\n", rank, i_message);
    printf("Número total de procesos: %d\n", size);
  }
  else if (rank != 0 && rank != (size-1)) {
    MPI_Recv(&i_message, i_message_elements, MPI_INT, rank-1, tag, MPI_COMM_WORLD, &status);
    i_message = add(rank, i_message);
    MPI_Send(&i_message, i_message_elements, MPI_INT, rank+1, tag, MPI_COMM_WORLD);
  }
  else if (rank == size-1){
    MPI_Recv(&i_message, i_message_elements, MPI_INT, rank-1, tag, MPI_COMM_WORLD, &status);
    i_message = add(rank, i_message);
    MPI_Send(&i_message, i_message_elements, MPI_INT, 0, tag, MPI_COMM_WORLD);
  }

  MPI_Finalize();
    return 0;
}

int add (int rank, int i) {
  printf("El proceso %d recibe i = [%d]\n", rank, i);
  printf("El proceso %d envia i = [%d]\n", rank, ++i);
  return i;
}