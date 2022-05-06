# SimpleMPI
Assignment for MPI and openMPI.

There are 3 directories.
- doc is for Assignment requirements.
- mpi is a project which is using MPI.
	To run this project, please do the following steps.
	* Change into mpi directory
		cd mpi
	* Build the project
		make
	* Run the project via MPI
		mpirun -np <process number> ./mpi_exam <exam number>
		e.g.
		mpirun -np 2 ./mpi_exam 5
	* Then you will see the result.
- omp is a project which using OpenMPI
	To run this project, please do the following steps.
	* Change into omp directory
		cd omp
	* Build the project
		make
	* Run the project via MPI
