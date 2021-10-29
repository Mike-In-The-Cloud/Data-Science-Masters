#include <omp.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int max_size = 100000;

int main(int argc, char *argv[])
{
   double told[max_size], t[max_size], tol, diff, difmax, priv_difmax;
   double tstart, tstop;
   register int i, iter;
   int nthreads, n;
   printf("enter the problem size (n) and the convergence tolerance\n");
   scanf("%d %lf", &n, &tol);
   printf("Enter the number of threads (max 10) ");
   scanf("%d", &nthreads);

   tstart = omp_get_wtime();

// initialise temperature array
#pragma omp parallel for schedule(static) default(shared) private(i)

   for (i = 1; i <= n; i++)
   {
      t[i] = 20.0;
   }
   // fix end points as cold and hot
   t[0] = 100.0;
   t[n + 1] = 0.0;

   iter = 0;
   difmax = 1000000.0;

   while (difmax > tol)
   {

      iter = iter + 1;

      //populate tnew array to keep old values for calculating residual
      for (i = 1; i <= n; i++)
      {
         told[i] = t[i];
      }
// update temperature for next iteration
#pragma omp parallel for schedule(static) default(shared) private(i)

      for (i = 1; i <= n; i++)
      {
         t[i] = (t[i - 1] + t[i + 1]) / 2.0;
      }
      // work out maximum difference between old and new temperatures
      difmax = 0.0;
       
#pragma omp parallel default(shared) private(i, diff, priv_difmax)
      {
         priv_difmax = 0.0;
#pragma omp for schedule(guided)
         for (i = 1; i <= n; i++)
         {
            diff = fabs(t[i] - told[i]);
            if (diff > priv_difmax)
            {
               priv_difmax = diff;
            }
         }
#pragma omp critical
         if (priv_difmax > difmax)
         {
            difmax = priv_difmax;
         }
      }

   } //while (difmax>tol)

   tstop = omp_get_wtime();

   /* 
    for (i=1; i <= n; i++) {
        printf("told[%d] = %-5.7lf  \n", i, t[i]);
    }
    printf("iterations = %d  maximum difference = %-5.7lf  \n", iter, difmax);
     */

   printf("time taken is %4.3lf\n", (tstop - tstart));
}
