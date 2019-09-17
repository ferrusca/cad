/**
 * Modo sincrono -> seguro
 * modo list     -> menor overhead en el sistema (asíncrono-> MPI_Isend, MPI_Irecv)
 * modo buffer   -> separa el emisor del receptor
 * modo normal   -> no hay garantía (comprometido)

  MPI_Wait(MPI_Request &request, MPI_Status &status) se espera como wait(), 
  a que termine el envío y recepcion  de datos para poder continuar con el programa (deadlock).

  MPI_Waitall(number of process, &req[i], &status[i]) espera a que termine cuando hay envío paara todos los procesos


 */

int main(int argc, char const *argv[])
{
  /* code */
  return 0;
}