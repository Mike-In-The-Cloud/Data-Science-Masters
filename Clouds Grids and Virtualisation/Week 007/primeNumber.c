# include <stdlib.h>
# include <stdio.h>
# include <omp.h>

int main ( int argc, char *argv[] );
int prime_number ( int n );


int main ( int argc, char *argv[] )
{
  int  maxNumber = 100000;
  int primes;
  double start, end;
  int* pMaxNumber = &maxNumber;
  int* pPrimes = &primes;

  printf ( "\n" );
  printf ( "PRIME_OPEN_MP\n" );
  printf ( "  C/OpenMP version\n" );

  printf ( "\n" );
  printf ( "  Number of processors available = %d\n", omp_get_num_procs ( ) );
  printf ( "  Number of threads =              %d\n", omp_get_max_threads ( ) );
  
  //Start timer here
  start = omp_get_wtime();
  
  *pPrimes = prime_number ( *pMaxNumber );
  end = omp_get_wtime();
  //End Timer here
  
  
  printf ( "maxNumber        Primes        \n" );
  printf ( "  %8d  %8d  \n", *pMaxNumber, *pPrimes);

  printf ( "\n" );
  printf ( "PRIME_OPEN_MP\n" );
  printf ( "  Normal end of execution.\n" );

  printf("Work took %f seconds\n", end - start);
  return 0;
}




int prime_number ( int n )
/*
  Purpose: PRIME_NUMBER returns the number of primes between 1 and N
  Author: John Burkardt
  Parameters:
    Input, int n, the maximum number to check.
    Output, int PRIME_NUMBER, the number of prime numbers up to N.
*/
{
  int i,j,prime;
  int total = 0;

# pragma omp parallel shared ( n ) private ( i, j, prime ) reduction ( + : total ) num_threads(24)

# pragma omp for schedule(guided)
  for ( i = 2; i <= n; i++ )
  {
    prime = 1;

    for ( j = 2; j < i; j++ )
    {
      if ( i % j == 0 )
      {
        prime = 0;
        break;
      }
    }
    total = total + prime;
  }

  return total;
}
