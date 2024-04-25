CC=cc
F90=ftn
PRGENV=${PE_ENV}
CFLAGS=-g
SOURCE=hello-omp.c
EXE=hello-omp.out
ifeq ($(PRGENV),INTEL)
	OMP_FLAG=-openmp
else ifeq ($(PRGENV),GNU)
	OMP_FLAG=-fopenmp
else ifeq ($(PRGENV),CRAY)
	OMP_FLAG=-homp
endif 

all: hello-omp

hello-omp:
	$(CC) $(CFLAGS) $(SOURCE) -o $(EXE) $(OMP_FLAG)
clean:
	rm -rf $(EXE)
