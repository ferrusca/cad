#include <stdio.h>
#include <mpi.h>
#include <string.h>

int main(int argc, char** argv) {
  int rank, size, origen, destino, tag = 1;
  int mensaje[100];
  MPI_Status status; // estructura con informacion de la comunicacion
  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  //el nodo 0 es el proceso principal
  if (rank != 0) {
    printf("Proceso %d de %d\n", rank, size);
    sprintf(mensaje,"Saludos desde el proceso %d.", rank);
    destino = 0;
    MPI_Send(mensaje, strlen(mensaje)+1, MPI_CHAR, destino, tag, MPI_COMM_WORLD);
  } else {
    printf("Proceso 0, total de procesos: %d\n", size);
    // El proceso 0 recibira los datos de los procesos 1-Ssx9
    for (origen = 1; origen < size; ++origen) {
      MPI_Recv(mensaje, 100, MPI_CHAR, origen, tag, MPI_COMM_WORLD, &estatus);
      printf("%s\n", mensaje);
    }
  }
  MPI_Finalize();
  return 0;
}

// TAREA: Ver ejemplo 3. poner print en cada nodo cuando cuando recibe y envía 
// el nodo 0 debe recibir i+3 cuando hay 4 nodos (cada uno suma 1 unidad) 
// hasta el prox martes

for nodo = 0; nodo < size {
  MPI_Send(i, nodo + 1)
  print("enviando...")
}
for nodo = 0; nodo < size {
  MPI_Recv(i, nodo)
  print("recibiendo")
  print (i)
}