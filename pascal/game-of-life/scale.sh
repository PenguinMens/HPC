#!/bin/bash
#

# Check if the executable path and version name are provided as parameters

make clean
make COMPILER=CRAY PROFILER=ON cpu_openmp_task_cc
make COMPILER=CRAY PROFILER=ON cpu_openmp_loop_cc


# Set other variables
mkdir ./scaling/
mkdir ./scaling/loop/
executable_path="./bin/02_gol_cpu_openmp_loop" 
nsteps=10
for nomp in 1 2 4 8 16; do
    for grid in 10 100 1000 10000 40000; do

        echo "Running with ${nomp} threads and ${grid}x${grid} grid"
        export OMP_NUM_THREADS=${nomp}
        
        basename=GOL-loop-.nomp-${nomp}.ngrid-${grid}x${grid}.${nsteps}
        log_file=scaling/loop/${basename}.log
       
        ${executable_path}  ${grid} ${grid}  ${nsteps} 0 -1 > ${log_file}

    done
done
mkdir ./scaling/
mkdir ./scaling/task/
executable_path="./bin/02_gol_cpu_openmp_task" 
nsteps=10
for nomp in 1 2 4 8 16; do
    for grid in 10 100 1000 10000 40000; do

        echo "Running with ${nomp} threads and ${grid}x${grid} grid"
        export OMP_NUM_THREADS=${nomp}
        
        basename=GOL-task-.nomp-${nomp}.ngrid-${grid}x${grid}.${nsteps}
        log_file=scaling/task/${basename}.log
       
        ${executable_path}  ${grid} ${grid}  ${nsteps} 0 -1 > ${log_file}

    done
done

# Set base name




# Export environment variable


# Run the executable with provided parameters and redirect output to log file

