CC=gcc-10
F90=ftn
PRGENV=${PE_ENV}
CFLAGS=-g -fopenmp
SOURCE=src

ifeq ($(PRGENV),INTEL)
	OMP_FLAG=-openmp
else ifeq ($(PRGENV),GNU)
	OMP_FLAG=-fopenmp
else ifeq ($(PRGENV),CRAY)
	OMP_FLAG=-homp
endif

all: hello serial omp-v1 omp-v2

hello:
	$(CC) $(CFLAGS) $(SOURCE)/hello-omp.c -o hello-omp $(OMP_FLAG)
serial:
	$(CC) $(CFLAGS) $(SOURCE)/pi-serial.c -o pi-serial $(OMP_FLAG)
omp-v1:
	$(CC) $(CFLAGS) $(SOURCE)/pi-omp-v1.c -o pi-omp-v1 $(OMP_FLAG)
omp-v2:
	$(CC) $(CFLAGS) $(SOURCE)/pi-omp-v2.c -o pi-omp-v2 $(OMP_FLAG)
omp-v3:
	$(CC) $(CFLAGS) $(SOURCE)/pi-omp-v3.c -o pi-omp-v3 $(OMP_FLAG)
clean:
	rm -rf hello-omp pi-serial pi-omp-v1 pi-omp-v2 pi-omp-v3
