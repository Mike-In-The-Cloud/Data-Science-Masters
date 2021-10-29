#include <stdio.h>
#include <omp.h>
#include <stdlib.h>
#define THREADS 8
int main(int argc, char *argv[])
{
	int tid, nthreads;

        if ( argc > 1 )
        {
           omp_set_num_threads( atoi(argv[1]) );
        } else {
	   omp_set_num_threads(THREADS);
        }
        int j; 
        double start, finish;
        start = omp_get_wtime();

	// start of parallel section
	// Fork a team of threads with each thread having a private tid variable
	#pragma omp parallel private(tid)
	{
		tid=omp_get_thread_num();
		printf("Hello world from thread %d\n", tid);
		/* Only master thread does this */
		if (tid == 0) {
			nthreads = omp_get_num_threads();
			printf("Number of threads = %d\n", nthreads);
		}


	}//end of parallel section
	// All threads join master thread and terminate
        finish = omp_get_wtime();

	printf("Time taken = %f(s)\n", finish-start);
	return 0;
}  // end main()
