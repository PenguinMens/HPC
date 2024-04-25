#include <omp.h>
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

int thread_id;
int counter =0;
#pragma omp parallel default(none) shared(counter) private(thread_id)
	{
		
		#pragma omp atomic 
		counter++;
	

		//thread_id =omp_get_thread_num();
		//printf("counter%d \n", counter);
		// //printf("thread %d started\n", thread_id);
		// char* hostname = (char*) malloc(256*sizeof(char));
		// gethostname(hostname,256*sizeof(char));
		// //printf("Hello world from thread %d on node %s and counter: %d\n",thread_id,hostname, counter);
		//printf("thread %d endedd\n", thread_id);
	}
	printf("counter%d \n", counter);

}





