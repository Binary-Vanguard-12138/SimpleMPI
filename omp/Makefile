EXECS=omp_exam

all: ${EXECS}

omp_exam: omp_exam.c
	gcc -fopenmp -o omp_exam omp_exam.c

clean:
	rm -f ${EXECS}

