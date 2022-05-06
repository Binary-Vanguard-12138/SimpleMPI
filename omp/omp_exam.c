#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

void Usage(char prog_name[]);
int main(int argc, char* argv[]) {
    int A_cnt = 0, B_cnt = 0, C_cnt = 0, D_cnt = 0, F_cnt = 0;
    int Test_Count;
    int i;
    int *data;
    /* check and get commad line arguments */
    if (argc != 2) Usage(argv[0]);
    Test_Count = strtol(argv[1], NULL, 10);     //Get number of exams from the commandline
    // Allocate space for array data
    data = malloc(Test_Count * sizeof(int));
    srandom(time(NULL));   // Seed the random number generator 
 
    for(i = 0; i < Test_Count; i++)
        data[i] = 50 + (100 - 50) * random()/((int) RAND_MAX);  // 50 <= data <= 100

    // Print list of grades
    printf("\nList of grades:\n");
    for(i = 0; i < Test_Count; i++)
        printf("%d ", data[i]);
    printf("\n\n"); 
    // count A, B, C, D, and F grades
    for(i = 0; i < Test_Count; i++){
        if (data[i] >= 90) 
        A_cnt++;
        else if (data[i] >= 80) 
        B_cnt++;
        else if (data[i] >= 70)
        C_cnt++;
        else if (data[i] >= 60)
        D_cnt++;
        else
        F_cnt++;
    }
// Print number of A, B, C, D, and F grades
    printf("Number of A = %d\n", A_cnt);
    printf("Number of B = %d\n", B_cnt);
    printf("Number of C = %d\n", C_cnt);
    printf("Number of D = %d\n", D_cnt);
    printf("Number of F = %d\n", F_cnt);
}

void Usage(char prog_name[]){
   fprintf(stderr, "usage: %s ", prog_name);
   fprintf(stderr, "<number of tests>\n");
   exit(0);
}