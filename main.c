#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <mpi.h>

#define MAX_DATA_SIZE pow(2, 10)  // Example: 2^10 as the maximum data size

int main(int argc, char *argv[]) {
    int rank, size;
    float *data = NULL;  // This will hold our data

    // Initialize MPI
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // Data generation: Only the root (rank 0) will generate the data
    if (rank == 0) {
        data = (float*) malloc(MAX_DATA_SIZE * sizeof(float));
        if (data == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            MPI_Abort(MPI_COMM_WORLD, EXIT_FAILURE);
        }

        // Fill the data array with random floating-point numbers
        for (int i = 0; i < MAX_DATA_SIZE; i++) {
            data[i] = (float)rand() / RAND_MAX;  // Random float between 0 and 1
        }
    }

    double start_time, end_time, mpi_bcast_time;

    // Using MPI_Bcast()
    start_time = MPI_Wtime();
    MPI_Bcast(data, MAX_DATA_SIZE, MPI_FLOAT, 0, MPI_COMM_WORLD);
    end_time = MPI_Wtime();
    mpi_bcast_time = end_time - start_time;

    // Output or store the timings
    printf("MPI_Bcast time: %f seconds\n", mpi_bcast_time);

    // Clean up
    if (rank == 0) {
        free(data);
    }

    MPI_Finalize();
    return 0;
}
