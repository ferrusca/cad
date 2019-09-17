/**
  * Calculo de PI (mpi).
  * Se utiliza la integral de 1/(1+x²) dx [0,1] = pi/4
  *
  */

#include <stdio.h>
#include <mpi.h>
#include <math.h> // fabs()

double f (double a) {
  return 4.0 / (1.0 + a * a);
}

int main(int argc, char** argv) {
  int n, i, rank, size;
  double PI25DT = 3.141592653589793238462643;
  double mypi, pi, h, sum, x;
  int source, dest, tag = 100;
  MPI_Status status;
  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  printf("Proceso %d de %d\n", rank, size);
  n = 100;
  h = 1.0/(double)n;
  sum = 0.0;
  for (i = rank+1; i <= n; i += size)
  {
    printf("Proceso %d computando n = %d \n", rank, i);
    x = h * ((double)i - 0.5);
    sum += f(x);
  }
  mypi = h * sum;
  printf("Proceso %d, mypi: %.16f\n", rank, mypi);
  if (rank == 0){
    pi = mypi;
    for (i = 1; i < size; ++i) 
    {
      source = i;
      MPI_Recv(&mypi, 1, MPI_DOUBLE, source, tag, MPI_COMM_WORLD, &status);
      pi += mypi;
      printf("PI es aproximadamente %.16f, el error cometido es %.16f\n", pi, fabs(pi - PI25DT));
    }
  } else {
    dest = 0;
    MPI_Send(&mypi, 1, MPI_DOUBLE, dest, tag, MPI_COMM_WORLD);
  }
  MPI_Finalize();
  return 0;
}