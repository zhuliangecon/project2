#include "headers.h"

int main(int argc, char **argv) {
    MPI_Init(&argc, &argv);
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int N_values[] = {1 << 10, 1 << 12, 1 << 14, 1 << 16};

    for (int i = 0; i < sizeof(N_values) / sizeof(int); i++) {
        int N = N_values[i];
        float *data = (float *) malloc(sizeof(float) * N); // 在所有进程中分配内存
        if (data == NULL) {
            fprintf(stderr, "Memory allocation failed for data.\n");
            MPI_Abort(MPI_COMM_WORLD, EXIT_FAILURE);
        }
        
        if (rank == 0) {
            // 假设generate_data填充了data的内存，并返回了data。 
            data = generate_data(N); // 修改generate_data，使其接受data指针并填充它
        }
        
        // 使用MPI_Bcast测量时间
        double time_taken_mpi = measure_time(data, N, MPI_Bcast);
        
        // 使用MY_Bcast测量时间
        double time_taken_my = measure_time(data, N, MY_Bcast);
        
        int num_procs;
        MPI_Comm_size(MPI_COMM_WORLD, &num_procs);

        int n_value = get_n_from_size(N);

        if (rank == 0) {
            printf("N = 2^%d, P = %d: \n",n_value, num_procs);
            printf("%f seconds using MPI_Bcast \n", time_taken_mpi);
            printf("%f seconds using MY_Bcast  \n",  time_taken_my);
        }
        free(data);  // 在所有进程中释放内存
    }

    MPI_Finalize();
    return 0;
}
