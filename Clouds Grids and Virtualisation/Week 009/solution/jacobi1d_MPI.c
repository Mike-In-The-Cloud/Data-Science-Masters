// To Compile:
// mpicc jacobi1d_MPI.c

//To Run:
// mpiexec -n 2 a.out

#include "mpi.h" /* Includes the MPI library */
#include <stdio.h>
#include <math.h>

int max_size=100000;

int main(int argc, char *argv[])
{
double told[max_size], t[max_size], tol, diff, difmax, tempd;
int i, iter, n;
int proc_num, nprocs, WNei, ENei; /* integers to hold process number, number of processes and number of neighbouring processes */
MPI_Status status; /* status used by MPI_Recv */

MPI_Init(&argc, &argv); /* Initialise MPI */
MPI_Comm_size(MPI_COMM_WORLD, &nprocs); /* Get number of processors and store it in nprocs (from command line) */
MPI_Comm_rank(MPI_COMM_WORLD,&proc_num); /* Get processor number and store it in proc_num */

   WNei = proc_num - 1; /* My West neighbour is one process number lower */
   ENei = proc_num + 1; /* My West neighbour is one process number higher */
   if (proc_num == 0) WNei=-1;  /*First processor has no West neighbour so set WNei to -1*/
   if (proc_num == nprocs-1) ENei=-1;  /*Last processor has no East neighbour so set ENei to -1*/

n = 32; /* Fixed Cell probmlem Example, note in this example n should be divisible by nprocs */
//n = 4*nprocs; /* Strong Scaling Example i.e. problem becomes 4 times the number of processors*/ 
tol = 0.001;

n = n/nprocs; /* Split problem up,  */

// initialise temperature array
for (i=1; i <= n; i++) {
   told[i] = 20.0;
   }
// fix end points as cold and hot
if(proc_num == 0) told[0] = 0.0; /* Cold Point only exists on first processor */
if(proc_num == nprocs-1) told[n+1] = 100.0; /* Hot Point only exists on last processor */

iter = 0;
difmax = 1000000.0;

while (difmax > tol) {
iter=iter+1;

//for(iter=1;iter<=10;iter++) {

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


   MPI_Allreduce(&difmax,&tempd,1,MPI_DOUBLE,MPI_MAX,MPI_COMM_WORLD); /* Takes in the dif max of each process and redistributes the maximum into a temporary variable tempd */
   difmax = tempd;   

// MPI send and recv for 2 processors     
/*
   if(proc_num == 0) {
   MPI_Send(&told[n],1,MPI_DOUBLE,1,0, MPI_COMM_WORLD);	   
   MPI_Recv(&told[n+1],1,MPI_DOUBLE,1,0, MPI_COMM_WORLD, &status);   
   }
   
   if(proc_num == 1) {
   MPI_Recv(&told[0],1,MPI_DOUBLE,0,0, MPI_COMM_WORLD, &status);
   MPI_Send(&told[1],1,MPI_DOUBLE,0,0, MPI_COMM_WORLD);	   
   }   
*/   

// Odd and even send and recv
   if(proc_num % 2 == 0) {  /*For even Processor Numbers*/
       if(WNei >= 0) MPI_Send(&told[1],1,MPI_DOUBLE,WNei,WNei, MPI_COMM_WORLD);  /*Send to West*/
	   if(ENei >= 0) MPI_Recv(&told[n+1],1,MPI_DOUBLE,ENei,proc_num, MPI_COMM_WORLD, &status); /*Receive From East*/
	   if(WNei >= 0) MPI_Recv(&told[0],1,MPI_DOUBLE,WNei,proc_num, MPI_COMM_WORLD, &status); /*Receive From West*/
	   if(ENei >= 0) MPI_Send(&told[n],1,MPI_DOUBLE,ENei,ENei, MPI_COMM_WORLD); /*Send to East*/
	   	}
      else { /*For odd Processor Numbers */
       if(ENei >= 0) MPI_Recv(&told[n+1],1,MPI_DOUBLE,ENei,proc_num, MPI_COMM_WORLD, &status); /*Receive From East*/
	   if(WNei >= 0) MPI_Send(&told[1],1,MPI_DOUBLE,WNei,WNei, MPI_COMM_WORLD); /*Send to West*/
	   if(ENei >= 0) MPI_Send(&told[n],1,MPI_DOUBLE,ENei,ENei, MPI_COMM_WORLD); /*Send to East*/
	   if(WNei >= 0) MPI_Recv(&told[0],1,MPI_DOUBLE,WNei,proc_num, MPI_COMM_WORLD, &status); /*Receive From West*/
	}   
   
    if(proc_num==0) printf("iterations = %d  maximum difference = %-5.7lf \n", iter, difmax);

}//while (difmax > tol)



   for (i=1; i <= n; i++) {
      printf("told[%d] = %-5.7lf  \n", i, t[i]);
      }
   printf("iterations = %d  maximum difference = %-5.7lf  \n", iter, difmax);
   
MPI_Finalize();   
   
}

