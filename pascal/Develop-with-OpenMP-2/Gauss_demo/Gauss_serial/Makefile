CC = cc
F90 = ftn
MPICC = cc
MPIF90 = ftn
INC= -I ./include
OPT_FLAGS = -g

all: serial 

serial:
	cc src/gaussian.c src/gauss_serial.c -o gauss-serial $(INC)

clean:
	rm -r gauss-serial 

