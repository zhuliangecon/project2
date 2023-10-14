#include "headers.h"
// function to generate random data
void generate_data(float* data, int N) {
    for (int i = 0; i < N; i++) {
        data[i] = (float)rand() / (float)(RAND_MAX);
    }
}
// function to measure broadcast time 
double measure_time(float *data, int N, int (*bcast_function)(void*, int, MPI_Datatype, int, MPI_Comm)) {

    // Warmup
    int warmup_iterations = 3;
    for (int i = 0; i < warmup_iterations; ++i) {
        MPI_Bcast(data, N, MPI_FLOAT, 0, MPI_COMM_WORLD);
        MPI_Barrier(MPI_COMM_WORLD);
    }  

    // Synchronize all processes before starting the timer
    MPI_Barrier(MPI_COMM_WORLD);
    double start_time = MPI_Wtime();

    // Repeat the broadcast iterations times.
    int iterations = 1000;
    for (int i = 0; i < iterations; ++i) {

        bcast_function(data, N, MPI_FLOAT, ROOT, MPI_COMM_WORLD); 

        // Synchronize all processes at the end of each broadcast
        MPI_Barrier(MPI_COMM_WORLD);
    }

    // Synchronize all processes at the end of all broadcasts and stop the timer
    MPI_Barrier(MPI_COMM_WORLD);
    double end_time = MPI_Wtime();


    // Calculate and return the total time.
    double total_time = end_time - start_time;

    // Return the average time per broadcast
    return (total_time / iterations);
}


// Function to get n value from size
int get_n_from_size(int N) {
    int n = 0;
    while (N >>= 1) {
        n++;
    }
    return n;
}
// My implementation of MPI_Bcast using a binary tree
int MY_Bcast(void* buffer, int count, MPI_Datatype datatype, int root, MPI_Comm comm) {
    int rank, size;
    MPI_Request request;
    MPI_Status status;

    MPI_Comm_rank(comm, &rank);
    MPI_Comm_size(comm, &size);

    if (rank != root) {
        // Receive from the parent
        int src = (rank - 1) / 2;
        MPI_Irecv(buffer, count, datatype, src, 0, comm, &request);
        MPI_Wait(&request, &status);
    }

    // Send to left child
    int left_child = 2 * rank + 1;
    if (left_child < size) {
        MPI_Isend(buffer, count, datatype, left_child, 0, comm, &request);
        MPI_Wait(&request, &status);
    }

    // Send to right child
    int right_child = 2 * rank + 2;
    if (right_child < size) {
        MPI_Isend(buffer, count, datatype, right_child, 0, comm, &request);
        MPI_Wait(&request, &status);
    }

    return MPI_SUCCESS;
}


