#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>

int main(int argc, char** argv)
{
	int i;
	long long int sum, sum2;
	int a;
	int n;
	struct timeval startTime, stopTime;
	long totalTime;
	
int proc_num, nprocs;
MPI_Status status;

MPI_Init(&argc, &argv);
MPI_Comm_size(MPI_COMM_WORLD, &nprocs);
MPI_Comm_rank(MPI_COMM_WORLD,&proc_num);	
	
	n = 512*512;
	sum=0;

	gettimeofday(&startTime, NULL);
/* Cyclic distribution, i starts at proc_num+1 and increments by nproc. I.e if 2 processes, process 0 calculates i = 1,3,5,7 ... and process 1 calculates i = 2,4,6,8 ... */	
	for(i=proc_num+1; i<n+1; i=i+nprocs){ 
			a = i*i;
		//	printf("%d %d %d\n", i, a[i-1], proc_num);
			sum=sum + a;
	}
	gettimeofday(&stopTime, NULL);

    MPI_Allreduce(&sum,&sum2,1,MPI_LONG_LONG,MPI_SUM,MPI_COMM_WORLD);	
	
	totalTime = (stopTime.tv_sec * 1000000 + stopTime.tv_usec) - (startTime.tv_sec * 1000000 + startTime.tv_usec);

	printf("The sum of %d squares is %lld total %lld\n", n, sum, sum2);
	printf("%ld\n", totalTime);
	
MPI_Finalize();  	
}