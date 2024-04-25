#!/bin/bash -l
if [ $# -lt 4 ]; then
cat <<EOF
Usage:
 	$0 [maximum threads to use] [executable] [number of equations] [path to input matrix] [optional: file to write results] [optional: omp_schedule]
EOF

else
MAX_THREADS="$1"
EXE="$2"
NEQ="$3"
INPUT_DIR="$4"
OUTFILE="$5"
SCHEDULE="$6"


if [ ! -z ${OMP_SCHEDULE} ]; then
	export OMP_SCHEDULE=${SCHEDULE}
fi

if [ -z ${OUTFILE} ]; then
	OUTFILE="scaling_test"
elif [ -e ${OUTFILE} ]; then
       OUTFILE="scaling"
fi



for (( i=1; i<=${MAX_THREADS} ; i=$(expr $i \* 2) ))
	do
		export OMP_NUM_THREADS=$i
		echo $i
		echo -e "${OMP_NUM_THREADS} $(srun -N 1 -n 1 -c ${OMP_NUM_THREADS} ${EXE} -n ${NEQ} -f ${INPUT_DIR}/${NEQ}by${NEQ}.mat |grep  "Execution time" | cut -d "=" -f 2)">>${OUTFILE}.out
done


echo "Now using GNUPLOT to plot scaling"
module load gnuplot
gnuplot << EOF
	set term png
	set output "${OUTFILE}.png"
	plot "${OUTFILE}.out" using 1:2 with lines
EOF
fi
