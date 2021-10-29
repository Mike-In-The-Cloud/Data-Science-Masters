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

    ping_pong_count = 0;
    if (proc_num == 0)
        neighbour_num = 1;
    if (proc_num == 0)
        ping_pong_flag = 1;
    if (proc_num == 1)
        neighbour_num = 0;
    if (proc_num == 1)
        ping_pong_flag = -1;

    for (ping_pong_count = 1; ping_pong_count <= 10; ping_pong_count++)
    {
        ping_pong_flag = ping_pong_flag * -1;

        if (ping_pong_flag == 1)
        {
            printf("%d Sending %d \n", proc_num, ping_pong_count);
            sleep(1);
            MPI_Send(&i, 1, MPI_INT, neighbour_num, 0, MPI_COMM_WORLD);
        }

        if (ping_pong_flag == -1)
        {
            MPI_Recv(&i, 1, MPI_INT, neighbour_num, 0, MPI_COMM_WORLD, &status);
            printf("%d Recieved %d \n", proc_num, ping_pong_count);
            sleep(1);
        }
    }

    MPI_Finalize();
}
