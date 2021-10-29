#include <stdio.h>
#include <math.h>
#include <sys/time.h> // timing
#include <time.h> // timing

int max_size=100000;

int main(int argc, char *argv[])
{

  //The variables for the start and stop timer
	struct timeval startTime, stopTime;
    // This variable will hold the total time
    long totalTime;


double told[max_size], t[max_size], tol, diff, difmax;
int i, iter, n;
printf("enter the problem size (n) and the convergence tolerance\n");
scanf("%d %lf", &n, &tol);


// Start timer: get current time and store it in variable startTime
    gettimeofday(&startTime, NULL);	
// initialise temperature array
for (i=1; i <= n; i++) {
   told[i] = 20.0;
   }
// fix end points as cold and hot
told[0] = 0.0;
told[n+1] = 100.0;

iter = 0;
difmax = 1000000.0;

while (difmax > tol) {

iter=iter+1;
// update temperature for next iteration
for (i=1; i <= n; i++) {
   t[i] = (told[i-1]+told[i+1])/2.0;
   }
// work out maximum difference between old and new temperatures
difmax=0.0;
for (i=1; i <= n; i++) {
   diff = fabs(t[i]-told[i]);
   if (diff > difmax) {
      difmax = diff;
      }
   told[i] = t[i];
   }

}//while (difmax > tol)



   for (i=1; i <= n; i++) {
      printf("told[%d] = %-5.7lf  \n", i, t[i]);
      }
   printf("iterations = %d  maximum difference = %-5.7lf  \n", iter, difmax);
   
// Stop timer: get current time and store it in variable stopTime
    gettimeofday(&stopTime, NULL);
    // Calculate total time by subracting the startTime from the stopTime (result is in microseconds)
    totalTime = (stopTime.tv_sec * 1000000 + stopTime.tv_usec) - (startTime.tv_sec * 1000000 + startTime.tv_usec);
    
    // print statement - int, unsigned long int, long
    printf("Time taken: %ld microseconds\n", totalTime);
}

