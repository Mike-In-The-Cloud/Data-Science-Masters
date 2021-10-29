#include <stdio.h>
#include <stdlib.h>
#include <omp.h> // open mp

#define THREADS 4

int main(){

    int tid;
    omp_set_num_threads(THREADS);

    #pragma omp parallel private(tid)
    {
        tid = omp_get_thread_num();
        printf("Hello world from thread %d\n", tid);

        if(tid ==0)
        {
            int nthreads = omp_get_num_threads();
            printf("Number of threads = %d\n", nthreads);

        }
    }

    return 0;
}