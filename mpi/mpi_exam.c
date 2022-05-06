#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MASTER_PROCESS 0

void Usage(char prog_name[]);

int main(int argc, char* argv[]) {
    int world_size = 0, world_rank = 0;

    int A_cnt = 0, B_cnt = 0, C_cnt = 0, D_cnt = 0, F_cnt = 0;
    int local_A_cnt = 0, local_B_cnt = 0, local_C_cnt = 0, local_D_cnt = 0, local_F_cnt = 0;
    int Test_Count;
    int i;
    int *data = NULL;
    /* check and get commad line arguments */
    if (argc != 2) Usage(argv[0]);
    Test_Count = strtol(argv[1], NULL, 10);     //Get number of exams from the commandline

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    int rem = Test_Count % world_size;
    int sum = 0;
    int *sendcounts = calloc(world_size, sizeof(int));
    int *displs = calloc(world_size, sizeof(int));
    int localnum = Test_Count / world_size + 1;
    int *local_data = calloc(localnum, sizeof(int));

    // calculate send counts and displacements
    for (int i = 0; i < world_size; i++) {
        sendcounts[i] = Test_Count/world_size;
        if (rem > 0) {
            sendcounts[i]++;
            rem--;
        }

        displs[i] = sum;
        sum += sendcounts[i];
    }

	int local_data_cnt = sendcounts[world_rank];

    // print calculated send counts and displacements for each process
    if (MASTER_PROCESS == world_rank) {
        for (int i = 0; i < world_size; i++) {
            printf("sendcounts[%d] = %d\tdispls[%d] = %d\n", i, sendcounts[i], i, displs[i]);
        }
    }

    if (MASTER_PROCESS == world_rank) {
    	// Allocate space for array data
	    data = calloc(Test_Count, sizeof(int));
    	srandom(time(NULL));   // Seed the random number generator

        // Generate random data in root process
        for(i = 0; i < Test_Count; i++)
            data[i] = 50 + (100 - 50) * random()/((int) RAND_MAX);  // 50 <= data <= 100
    }
    // divide the data among processes as described by sendcounts and displs
    MPI_Scatterv(data, sendcounts, displs, MPI_INT, local_data, localnum, MPI_INT, MASTER_PROCESS, MPI_COMM_WORLD);
	
    // Print list of grades
    printf("Scattered data at rank %d {", world_rank);
    for (int i = 0; i < local_data_cnt; i ++) {
        if (i == sendcounts[world_rank] - 1) {
            printf("%d}\n", local_data[i]);
        } else {
            printf("%d, ", local_data[i]);
        }
    }
    // count A, B, C, D, and F grades
    for(i = 0; i < local_data_cnt; i++){
        if (local_data[i] >= 90) 
        	local_A_cnt++;
        else if (local_data[i] >= 80) 
        	local_B_cnt++;
        else if (local_data[i] >= 70)
	        local_C_cnt++;
        else if (local_data[i] >= 60)
        	local_D_cnt++;
        else
        	local_F_cnt++;
    }
// Print number of A, B, C, D, and F grades
    printf("Process[%d] Number of A = %d\n", world_rank, local_A_cnt);
    printf("Process[%d] Number of B = %d\n", world_rank, local_B_cnt);
    printf("Process[%d] Number of C = %d\n", world_rank, local_C_cnt);
    printf("Process[%d] Number of D = %d\n", world_rank, local_D_cnt);
    printf("Process[%d] Number of F = %d\n", world_rank, local_F_cnt);

	MPI_Reduce(&local_A_cnt, &A_cnt, 1, MPI_INT, MPI_SUM, MASTER_PROCESS, MPI_COMM_WORLD);
	MPI_Reduce(&local_B_cnt, &B_cnt, 1, MPI_INT, MPI_SUM, MASTER_PROCESS, MPI_COMM_WORLD);
	MPI_Reduce(&local_C_cnt, &C_cnt, 1, MPI_INT, MPI_SUM, MASTER_PROCESS, MPI_COMM_WORLD);
	MPI_Reduce(&local_D_cnt, &D_cnt, 1, MPI_INT, MPI_SUM, MASTER_PROCESS, MPI_COMM_WORLD);
	MPI_Reduce(&local_F_cnt, &F_cnt, 1, MPI_INT, MPI_SUM, MASTER_PROCESS, MPI_COMM_WORLD);

	if (MASTER_PROCESS == world_rank) {
    	printf("Number of A = %d\n", A_cnt);
	    printf("Number of B = %d\n", B_cnt);
	    printf("Number of C = %d\n", C_cnt);
	    printf("Number of D = %d\n", D_cnt);
    	printf("Number of F = %d\n", F_cnt);
	}
    MPI_Finalize();
    free(sendcounts);
    free(displs);
	free(local_data);
	if (data) free(data);
}

void Usage(char prog_name[]){
   fprintf(stderr, "usage: %s ", prog_name);
   fprintf(stderr, "<number of tests>\n");
   exit(0);
}
