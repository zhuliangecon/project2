#include "headers.h"

int main(int argc, char **argv) {
    MPI_Init(&argc, &argv);
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    // set N values in powers of 2
    int N_values[] = {1 << 10, 1 << 12, 1 << 14, 1 << 16};

    for (int i = 0; i < sizeof(N_values) / sizeof(int); i++) {
        int N = N_values[i];
        float *data = (float *) malloc(sizeof(float) * N); // allocate memory for data on each process
        if (data == NULL) {
            fprintf(stderr, "Memory allocation failed for data.\n");
            MPI_Abort(MPI_COMM_WORLD, EXIT_FAILURE); // abort if memory allocation failed
        }
        
        if (rank == 0) {
            data = generate_data(N); // generate data in root process
        }
        
        // measure broadcast time on root using MPI_Bcast
        double time_taken_mpi = measure_time(data, N, MPI_Bcast);
        
        // measure broadcast time on root using MY_Bcast
        double time_taken_my = measure_time(data, N, MY_Bcast);
        
        int num_procs;
        MPI_Comm_size(MPI_COMM_WORLD, &num_procs);

        // get expression for 2^n
        int n_value = get_n_from_size(N);

        if (rank == 0) {
            printf("N = 2^%d, P = %d: \n",n_value, num_procs);
            printf("%f seconds using MPI_Bcast \n", time_taken_mpi);
            printf("%f seconds using MY_Bcast  \n",  time_taken_my);
        }
        free(data);  // free memory
    }

    MPI_Finalize();
    return 0;
}
