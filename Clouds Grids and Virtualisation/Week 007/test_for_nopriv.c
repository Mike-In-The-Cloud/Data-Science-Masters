#include <omp.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>    // time()

int main(int argc, char *argv[]) {
    int max_size=40000;
    
    int glob_max;
    int a[max_size];
    int i,k,totalTests;
    int nthreads;
    int n=100;
    
   
    totalTests = atoi(argv[1]);
    nthreads = atoi(argv[2]);
    
    //initialize array with random numbers
    srand(time(NULL));
    for (i=0; i<n; i++) {
        a[i]=rand();
    }
    
    //Run multiple tests to check for disagreement
    //between serial and parallel calculation
    for (k=0;k<totalTests;k++) {
		
		//find maximum value of array with serial code
        int serialMax = 0;
        for (i=0; i<n; i++) {
            if (a[i]>serialMax) {
                serialMax = a[i];
            }
        }
        
        //find maximum value of array with parallel code
        //without using private variable to store max for each thread
        glob_max = 0;
        omp_set_num_threads(nthreads);
        #pragma omp parallel shared(glob_max,a) private (i)
        {
            #pragma omp for
            for (i=0; i < n; i++) {
                if (a[i] > glob_max) {
                    glob_max = a[i];
                }
            }
                    
        }//omp parallel
        
        //Print "1" if the two calculations agree, else print "0"
        if (serialMax==glob_max)
            printf("1");
        else
            printf("0");
            
    } //for k
    
    printf("\n");
}
