CC=cc
F90=ftn
PRGENV=${PE_ENV}
FFLAGS=-g
NAME=pi-omp-v1
SOURCE=$(NAME).f90
OBJ=$(NAME).o
EXE=$(NAME).out

ifeq ($(PRGENV),INTEL)
	OMP_FLAG=-openmp
else ifeq ($(PRGENV),GNU)
	OMP_FLAG=-fopenmp
else ifeq ($(PRGENV),CRAY)
	OMP_FLAG=-homp
endif


%.o: %.f90
	$(F90) -c -o $@ $< $(FFLAGS) $(OMP_FLAG)
pi-omp-v1: $(OBJ)
	$(F90) $(FFLAGS) $(OBJ) -o $(EXE) $(OMP_FLAG)

clean:
	rm -rf $(EXE) $(OBJ)
