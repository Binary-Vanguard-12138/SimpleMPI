EXECS=mpi_exam

MPICC?=mpicc

all: ${EXECS}

mpi_exam: mpi_exam.c
    ${MPICC} -o mpi_exam mpi_exam.c

clean:
    rm ${EXECS}