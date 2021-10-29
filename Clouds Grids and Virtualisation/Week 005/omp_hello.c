#include <stdio.h>
#include <omp.h>

int main(int argc, char** argv)
{

	int THREADS;

	printf("Enter the number threads to use : \n");
	
	scanf("%d", &THREADS);

	int tid, nthreads;
	double threadTime, threadStart, threadEnd; 
	
	
	omp_set_num_threads(THREADS);
	
	// start of parallel section
	// Fork a team of threads with each thread having a private tid variable
	#pragma omp parallel private(tid)
	{
		threadStart = omp_get_wtime();

		tid=omp_get_thread_num();

		printf("Hello world from thread %d .", tid);

		threadEnd = omp_get_wtime();

		printf("Time taken %f \n", threadEnd - threadStart);

		
		/* Only master thread does this */
		if (tid == 0) {
			nthreads = omp_get_num_threads();
			printf("Number of threads = %d .", nthreads);
			
			threadEnd = omp_get_wtime();

			printf("Master thread taken %f \n", threadEnd - threadStart);
		}
		threadTime += (threadEnd - threadStart);


	}//end of parallel section
	// All threads join master thread and terminate
	printf("\nTotal time: %f\n", threadTime);

	return 0;
}  // end main()
