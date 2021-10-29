#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    int proc_num, nprocs;
    int i, neighbour_num, ping_pong_count, ping_pong_flag;
    MPI_Status status;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &nprocs);
    MPI_Comm_rank(MPI_COMM_WORLD, &proc_num);

    i = 0;


// forward block
    if (proc_num == 0)
        printf("Number of Procs %d \n", proc_num);

    if (proc_num == 0)
    {
        printf("%d Sending to %d \n", proc_num, proc_num + 1);
        sleep(1);
        MPI_Send(&i, 1, MPI_INT, proc_num + 1, 0, MPI_COMM_WORLD);
    }

    if (proc_num > 0 && proc_num < nprocs - 1)
    {
        MPI_Recv(&i, 1, MPI_INT, proc_num - 1, 0, MPI_COMM_WORLD, &status);
        printf("%d Received from %d \n", proc_num, proc_num - 1);
        sleep(1);
        printf("%d Sending to %d \n", proc_num, proc_num + 1);
        sleep(1);
        MPI_Send(&i, 1, MPI_INT, proc_num + 1, 0, MPI_COMM_WORLD);
    }

    if (proc_num == nprocs - 1)
    {
        MPI_Recv(&i, 1, MPI_INT, proc_num - 1, 0, MPI_COMM_WORLD, &status);
        printf("%d Received from %d \n", proc_num, proc_num - 1);
        sleep(1);
    }

    if (proc_num == 0)
    {
        MPI_Recv(&i, 1, MPI_INT, proc_num + 1, 0, MPI_COMM_WORLD, &status);
        printf("%d Received from %d \n", proc_num, proc_num + 1);
        sleep(1);
    }

    if (proc_num > 0 && proc_num < nprocs - 1)
    {
        MPI_Recv(&i, 1, MPI_INT, proc_num + 1, 0, MPI_COMM_WORLD, &status);
        printf("%d Received from %d \n", proc_num, proc_num + 1);
        sleep(1);
        printf("%d Sending to %d \n", proc_num, proc_num - 1);
        sleep(1);
        MPI_Send(&i, 1, MPI_INT, proc_num - 1, 0, MPI_COMM_WORLD);
    }

    if (proc_num == nprocs - 1)
    {
        printf("%d Sending to %d \n", proc_num, proc_num - 1);
        sleep(1);
        MPI_Send(&i, 1, MPI_INT, proc_num - 1, 0, MPI_COMM_WORLD);
    }

    MPI_Finalize();
}
