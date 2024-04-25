!/*******************************************************
! * Calculating Pi with using midpoint rectangle method:*
! *  integral 4.0/(1+x^2) dx = pi	     	       	*
! *  or 						*
! *  summation (for i=0 to n) 4.0/(1+x_i^2)             *
! *  	where x_i = (i + 1/2) * delta x			*
! * 	   OpenMP Version 1	  			*
! *******************************************************/
program pi_serial
implicit none
integer*8 :: num_steps = 1000000000
integer i
real*8 :: PI_ref=3.1415926535897932,step,x,pi
real*8 :: summation=0.0
real   :: start,finish,omp_get_wtime
start=omp_get_wtime()
step = 1/(1.0 * num_steps)
	do i =1,num_steps
 ! Write an algorithm which first evaluates the 
 ! 	evaluate midpoint of ith rectangle (x_i)
 ! 	updates the sum by evaluating f(x) at x
	end do
 ! Uptade value of pi
finish=omp_get_wtime() 
	write(*,*) "Estimated value of pi =",pi
	write(*,*) "Error =", abs(PI_ref - pi)
	write(*,*) "Compute time=", (finish-start)," seconds"
	end


