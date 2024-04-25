CC=cc
F90=ftn
PRGENV=${PE_ENV}
CFLAGS=-g
SOURCE=src
INC= -I ./include
ifeq ($(PRGENV),INTEL)
	OMP_FLAG=-openmp
else ifeq ($(PRGENV),GNU)
	OMP_FLAG=-fopenmp
else ifeq ($(PRGENV),CRAY)
	OMP_FLAG=-homp
endif 

all: omp 

omp:
	cc src/gaussian.c src/gauss_omp.c -o gauss-omp $(INC) $(OMP_FLAG)

clean:
	rm -r gauss-omp

