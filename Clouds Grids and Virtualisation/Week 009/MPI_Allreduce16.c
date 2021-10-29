#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
  int proc_num, nprocs;
  MPI_Status status;
  int a, b;

  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &nprocs);
  MPI_Comm_rank(MPI_COMM_WORLD, &proc_num);

  a = proc_num;
  b = 0;

  printf("rank %d a_old %d b_old %d \n", proc_num, a, b);
  sleep(1);
  if (proc_num == 0)
    printf("Reducing \n");
  MPI_Allreduce(&a, &b, 1, MPI_INT, MPI_MAX, MPI_COMM_WORLD);
  sleep(1);
  printf("rank %d a_new %d b_new %d \n", proc_num, a, b);

  MPI_Finalize();
  return 0;
}