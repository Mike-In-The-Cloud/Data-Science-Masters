#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
  int proc_num, WNei, ENei, nprocs;
  MPI_Status status;
  double a;

  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &nprocs);
  MPI_Comm_rank(MPI_COMM_WORLD, &proc_num);
  a = 1.;
  WNei = proc_num - 1;
  ENei = proc_num + 1;
  if (proc_num == nprocs - 1)
    ENei = -1; /*For last processor set ENei to -1*/

  if (proc_num % 2 == 0)
  { /*For even Processor Numbers*/
    if (WNei >= 0)
      MPI_Send(&a, 1, MPI_DOUBLE, WNei, WNei, MPI_COMM_WORLD); /*Send to West*/
    if (WNei >= 0)
      printf("%d Sent to %d \n", proc_num, WNei);
    if (ENei >= 0)
      MPI_Recv(&a, 1, MPI_DOUBLE, ENei, proc_num, MPI_COMM_WORLD, &status); /*Receive From East*/
    if (ENei >= 0)
      printf("%d Recv from %d \n", proc_num, ENei);
    if (WNei >= 0)
      MPI_Recv(&a, 1, MPI_DOUBLE, WNei, proc_num, MPI_COMM_WORLD, &status); /*Receive From West*/
    if (WNei >= 0)
      printf("%d Recv from %d \n", proc_num, WNei);
    if (ENei >= 0)
      MPI_Send(&a, 1, MPI_DOUBLE, ENei, ENei, MPI_COMM_WORLD); /*Send to East*/
    if (ENei >= 0)
      printf("%d Sent to %d \n", proc_num, ENei);
  }
  else
  {
    if (ENei >= 0)
      MPI_Recv(&a, 1, MPI_DOUBLE, ENei, proc_num, MPI_COMM_WORLD, &status); /*Receive From East*/
    if (ENei >= 0)
      printf("%d Recv from %d \n", proc_num, ENei);
    if (WNei >= 0)
      MPI_Send(&a, 1, MPI_DOUBLE, WNei, WNei, MPI_COMM_WORLD); /*Send to West*/
    if (WNei >= 0)
      printf("%d Sent to %d \n", proc_num, WNei);
    if (ENei >= 0)
      MPI_Send(&a, 1, MPI_DOUBLE, ENei, ENei, MPI_COMM_WORLD); /*Send to East*/
    if (ENei >= 0)
      printf("%d Sent to %d \n", proc_num, ENei);
    if (WNei >= 0)
      MPI_Recv(&a, 1, MPI_DOUBLE, WNei, proc_num, MPI_COMM_WORLD, &status); /*Receive From West*/
    if (WNei >= 0)
      printf("%d Recv from %d \n", proc_num, WNei);
  }

  MPI_Finalize();
  return 0;
}