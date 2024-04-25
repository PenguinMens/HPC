#!/bin/bash
#

# Check if the executable path is provided as a parameter
if [ $# -ne 1 ]; then
    echo "Usage: $0 <executable_path>"
    exit 1
fi

executable_path=./bin/$1

# lets set some variables for a run. Here numbers are examples only.
nomp=2
nxgrid=10000
nygrid=10000
nsteps=2
echo executable_path=${executable_path} ${nxgrid} ${nygrid} ${nsteps}
# set some meaningful name. Could be reference, latests, etc.
someversionname=pre-serial
# set a base name
basename=GOL-$1-${someversionname}.nomp-${nomp}.ngrid-${nxgrid}x${nygrid}.${nsteps}
export OMP_NUM_THREADS=${nomp}
${executable_path} ${nxgrid} ${nygrid} ${nsteps} 0 -1 > logs/${basename}.log

mv GOL-stats.txt texts/${basename}.txt