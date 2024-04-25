! 
!	Exercise 1:
!	Intent : Write a helloworld program with OpenMP.
!
!	Goals: 
!		1. Include OpenMP header
!		2. Within the scope of #pragma omp parallel
!			a. Each thread queries it thread ID.
!			b. Each thread then prints its thread ID.
!
program hello90
integer:: id,nthreads,omp_get_thread_num,omp_get_num_threads
!Initialize omp parallel
! Call environment query to get thread id.
! Each thread then writes its thread id to stdout.
!end parallel
end program

