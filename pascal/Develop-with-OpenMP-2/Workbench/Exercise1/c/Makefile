CC=gcc
F90=ftn
PRGENV=${PE_ENV}
CFLAGS=-g -fopenmp
NAME=pi-serial
SOURCE=$(NAME).c
OBJ=$(NAME).o
EXE=$(NAME).out

ifeq ($(PRGENV),INTEL)
	OMP_FLAG=-openmp
else ifeq ($(PRGENV),GNU)
	OMP_FLAG=-fopenmp
else ifeq ($(PRGENV),CRAY)
	OMP_FLAG=-homp
endif


%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS) $(OMP_FLAG)

pi-serial: $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(EXE) $(OMP_FLAG)

clean:
	rm -rf $(EXE) $(OBJ)
