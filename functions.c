#include "headers.h"

float* generate_data(int N) {
    float *data = (float*)malloc(N * sizeof(float));
    if(data == NULL) {
        fprintf(stderr, "Memory allocation failed for N = %d\n", N);
        MPI_Abort(MPI_COMM_WORLD, EXIT_FAILURE);
    }
    
    for(int i = 0; i < N; i++) {
        data[i] = (float)rand() / RAND_MAX; // 随机生成0-1之间的浮点数
    }

    return data;
}

double measure_time(float *data, int N, int (*bcast_function)(void*, int, MPI_Datatype, int, MPI_Comm)) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    MPI_Barrier(MPI_COMM_WORLD); // 确保所有进程都已准备好
    double start_time = MPI_Wtime();

    bcast_function(data, N, MPI_FLOAT, ROOT, MPI_COMM_WORLD); 

    MPI_Barrier(MPI_COMM_WORLD); // 确保所有进程都已完成广播操作
    double end_time = MPI_Wtime();

    return (end_time - start_time);
}

int get_n_from_size(int N) {
    int n = 0;
    while (N >>= 1) {
        n++;
    }
    return n;
}