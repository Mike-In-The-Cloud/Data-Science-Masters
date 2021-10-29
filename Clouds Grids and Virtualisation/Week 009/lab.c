#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"
/*
#################
### psudocode ###
#################
read n from command line
sum = 0
for i=1 to n do
    a[i] = i*i
    print i + "" + a[i]
    sum = sum + a[i]
end do
print "The sum of" + n + "squares is " + sum
#################
###    end    ###
#################

TODO:

add timings to code
how quick does it run?
why does it run quicker without printing each loop?
plot a graph of run time againts n with and without printing each loop

*/
int main(int argc, char** argv)
{
    int input;
    int sum = 0;
    int i;
    int proc_num, nprocs; // processors 
    MPI_Status status;


	// We use atoi() to read an integer command line argument
    input = atoi(argv[1]);
    MPI_Init(&argc, &argv[2]);
    MPI_Comm_size(MPI_COMM_WORLD, &nprocs);
    MPI_Comm_rank(MPI_COMM_WORLD, &proc_num);
    


    


    for(i = proc_num + 1; i <= input; i++)
    {
        int result = 0;
        result = i * i;
        printf("%d + %d\n", i, result);
        sum = sum + result;
    }
    
    

    printf("\nThe sum of %d squares is %d\n", input, sum);
    MPI_Finalize();
	return 0;
}
