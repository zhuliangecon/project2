#include "headers.h"
// function to generate random data
void generate_data(float* data, int N) {
    for (int i = 0; i < N; i++) {
        data[i] = (float)rand() / (float)(RAND_MAX);
    }
}
// Function to measure broadcast time with guaranteed synchronization of processes
double measure_time(float *data, int N, int (*bcast_function)(void*, int, MPI_Datatype, int, MPI_Comm)) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    // Synchronize all processes at the start of the broadcast
    MPI_Barrier(MPI_COMM_WORLD); 
    double start_time = MPI_Wtime();

    bcast_function(data, N, MPI_FLOAT, ROOT, MPI_COMM_WORLD); 

    // Synchronize all processes at the end of the broadcast
    MPI_Barrier(MPI_COMM_WORLD);
    double end_time = MPI_Wtime();

    return (end_time - start_time);
}
// function to get n value from size
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


