#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
/*
	Exercise:
	Intent : Write a helloworld program with OpenMP.

	Goals:
		1. Include OpenMP header
		2. Within the scope of #pragma omp parallel
			a. Each thread queries it thread ID.
			b. Each thread then prints its thread ID.
*/

void main (){
	int thread_id = 0;
	//Initialize parallel region here
	{
		printf("Hello World from %d \n", thread_id);
	}
}
