#!/bin/bash -l
if [ $# -lt 3 ]; then
cat <<EOF
Usage:
 	$0 [executable] [number of steps] [filename for output] [optional: OMP_SCHEDULE]
EOF

else
EXE="$1"
STEPS="$2"
OUTFILE="$3"
SCHEDULE="$4"

if [ ! -z ${OMP_SCHEDULE} ]; then
	export OMP_SCHEDULE="${SCHEDULE}"
fi

if [ -e $OUTFILE ] ; then
	rm $OUTFILE
fi
for (( i=1; i<=8 ; i=$(expr $i \* 2) ))
	do
		export OMP_NUM_THREADS=$i
		echo "Executing srun -N 1 -n 1 -c ${OMP_NUM_THREADS} ${EXE} -n ${STEPS}"
		echo -e "${OMP_NUM_THREADS} $(srun -N 1 -n 1 -c ${OMP_NUM_THREADS} -n ${STEPS}|grep  "Compute time" | cut -d "=" -f 2 | cut -d " " -f 2)">>${OUTFILE}.out
done


echo "Now using GNUPLOT to plot scaling"
module load gnuplot
gnuplot << EOF
	set term png
	set output "${OUTFILE}.png"
	plot "${OUTFILE}.out" using 1:2 with lines
EOF
fi
