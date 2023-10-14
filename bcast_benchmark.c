#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

#define SIZE (1 << 16)

int main(int argc, char* argv[]) {
    int rank;
    double start, end, bcast_time; // 将多余的逗号替换为分号

    float data[SIZE];

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if(rank == 0) {
        for(int i = 0; i < SIZE; ++i) {
            data[i] = (float)rand() / (float)(RAND_MAX);
        }
    }

    // Warmup
    int warmup_iterations = 3;
    for (int i = 0; i < warmup_iterations; ++i) {
        MPI_Bcast(data, SIZE, MPI_FLOAT, 0, MPI_COMM_WORLD);
        MPI_Barrier(MPI_COMM_WORLD);
    }    

    // Synchronize all processes before starting the timer
    MPI_Barrier(MPI_COMM_WORLD);
    double start_time = MPI_Wtime();

    // Repeat the broadcast iterations times.
    int iterations = 100000;
    for (int i = 0; i < iterations; ++i) {

        MPI_Bcast(data, SIZE, MPI_FLOAT, 0, MPI_COMM_WORLD);

        // Synchronize all processes at the end of each broadcast
        MPI_Barrier(MPI_COMM_WORLD);
    }

    // Synchronize all processes at the end of all broadcasts and stop the timer
    MPI_Barrier(MPI_COMM_WORLD);
    double end_time = MPI_Wtime();


    // Calculate and return the total time.
    double total_time = end_time - start_time;

    // Return the average time per broadcast
    double avg_time = total_time / iterations;

    if(rank == 0) { // 只在节点0打印时间
        printf("Total bcast time: %f\n", avg_time);
    }

    MPI_Finalize();
    return 0;
}
