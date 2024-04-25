CC=cc
F90=ftn
PRGENV=${PE_ENV}
CFLAGS=-g
SOURCE=src

ifeq ($(PRGENV),INTEL)
	OMP_FLAG=-openmp
else ifeq ($(PRGENV),GNU)
	OMP_FLAG=-fopenmp
else ifeq ($(PRGENV),CRAY)
	OMP_FLAG=-homp
endif 

all: hello

hello:
	$(F90) $(CFLAGS) $(SOURCE)/hello-omp.f90 -o hello-omp $(OMP_FLAG)
clean:
	rm -rf hello-omp
