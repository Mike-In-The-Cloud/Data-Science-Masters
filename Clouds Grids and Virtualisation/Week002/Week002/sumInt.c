#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
	//loop variable
	int i;
	
	//variable to store the sum of integers
	int sum;
	
	//Initialize sum
	sum = 0;
	
	for (i=0; i<100000; i++) {
		sum = sum + i;
	}
	
	printf("The sum is %d\n",sum);
	
}
