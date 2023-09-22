#include <mpi.h>
#include <stdio.h>
// based on lecture slides Topic 3. p.30
int main(int argc, char *argv[]) 
{
    int rank, size;
    MPI_Init(&argc, &argv); 
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // synochronize all processes
    MPI_Barrier(MPI_COMM_WORLD);

    // print by rank
    for (int i = 0; i < size; i++) {
        if (rank == i) {
            printf("Hello from %d of %d processors.\n", rank, size);
        }
        // synochronize all processes again
        MPI_Barrier(MPI_COMM_WORLD);
    }

    MPI_Finalize();
    return 0;
}