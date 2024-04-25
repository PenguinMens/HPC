#!/bin/bash -l
#SBATCH --nodes=1
#SBATCH --account=
#SBATCH --reservation=
#SBATCH --job-name=openmp-tutorial
#SBATCH --time=00:20:00
#SBATCH --export=NONE

# To change the number of threads, alter the cpus-per-task directive
# for SBATCH and the variable OMP_NUM_THREADS
export OMP_NUM_THREADS=

# update these as necessary
exe=
# if there are arguments then add this here
args=

srun -N -n 1 -c ${OMP_NUM_THREADS} ${exe} ${args}
