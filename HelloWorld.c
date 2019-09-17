/** 
  * Para compilar:   mpicc foobar.c -o foobar.o
  * Ejecutar:        mpirun -np 3 (np: numero de procesos a ejecutar) ./foobar.o
  */

#include <mpi.h>
#include <stdio.h>

int main(int argc, char const *argv[])
{
  int rank, size;

  // Inicia ejecución paralela
  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  printf("Hola desde el proceso %d de %d\n", rank, size);
  // Termina ejecución paralela
  MPI_Finalize();

  return 0;
}

// Para la ejecución distribuida, todas las UP deben tener mismo usuario y auth via llaves (nis)
// Sistema de archivos via red (/home/user)
// Sistemas de colas de procesos
// Sistemas de monitoreo (ganglia)
