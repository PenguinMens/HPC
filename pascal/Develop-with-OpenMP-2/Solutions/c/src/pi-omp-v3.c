/*************************************
 * Calculating Pi with using method: *
 *  integral 4.0/(1+x^2) dx = p	     *
 * 	   Serial Version	     *
 ************************************/
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

// Reference value to estimate error
double PI_ref=3.1415926535897932;
static long num_steps=1000000000;
static int MIN_NUM_STEPS=500000000;
double step;

double local_int(int start, int end, double delta)
{
  double sum = 0, x;
  for (int i=start; i<end; i++){
    x=(i+0.5) * delta;
    sum = sum + 4.0/(1.0+(x*x));
  }
  return sum;
}


// recursively split integration domain till small enough for one task
// this is NOT the optimal soluiton but is informative
double my_integrate(int start, int end, double delta) {
  int nsteps = (end - start);
  int nthreads = floor(nsteps/(double)MIN_NUM_STEPS);
  int midpoint = nsteps / 2+start;
  double sum=0.0;

  if (nthreads > 1) {
    #pragma omp parallel \
    default(none) shared(start,end,nthreads,sum,midpoint,delta) \
    num_threads(2) if (nthreads > 1)
    #pragma single
    {
        double sumleft, sumright;
        #pragma omp task shared(sumleft)
        {
          sumleft = my_integrate(start, midpoint, delta);
        }
        #pragma omp task shared(sumright)
        {
          sumright = my_integrate(midpoint, end, delta);
        }
        #pragma omp taskwait
        sum = sumleft + sumright;
    }
  }
  else
  {
    sum = local_int(start, end, delta);
  }
  return sum;
}

int main (int argc, char* argv[]){
	double start,stop,diff_time;
	double sum=0.0, pi;

	start= omp_get_wtime();
	step = 1.0 / (double) num_steps;
  sum = my_integrate(0, num_steps, step);
	pi = step * sum ;
	stop= omp_get_wtime();
	diff_time = (double) (stop-start);
	printf ("Estimated value of pi = %2.15lf\n",pi);
	printf ("Error = %2.15lf\n",fabs(PI_ref - pi));
	printf ("Compute time= %2.5lf seconds\n",diff_time);

}
