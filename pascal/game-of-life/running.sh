#!/bin/bash
#

# Check if the executable path and version name are provided as parameters
if [ $# -ne 2 ]; then
    echo "Usage: $0 <executable_name> <version_name>"
    exit 1
fi
make clean
make COMPILER=GCC PROFILER=ON cpu_serial_cc
executable_name=$1
someversionname=$2

# Define the executable path
executable_path=./bin/${executable_name}

# Set other variables
nomp=2
nxgrid=10000
nygrid=10000
nsteps=3

# Set base name
basename=GOL-${executable_name}-${someversionname}.nomp-${nomp}.ngrid-${nxgrid}x${nygrid}.${nsteps}

# Create a directory based on version name if it doesn't exist
mkdir -p logs/${someversionname}

# Set log file path
log_file=logs/${someversionname}/${basename}.log

# Export environment variable
export OMP_NUM_THREADS=${nomp}

# Run the executable with provided parameters and redirect output to log file
${executable_path} ${nxgrid} ${nygrid} ${nsteps} 0 -1 > ${log_file}

# Move the stats file
mv GOL-stats.txt texts/${basename}.txt
gprof -lbp ./bin/01_gol_cpu_serial gmon.out > logs/${someversionname}/analysis.txt