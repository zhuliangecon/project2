#ifndef HEADERS_H
#define HEADERS_H

#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

#define ROOT 0  // 设置广播的根节点为 0

// 函数声明
float* generate_data(int N);
double measure_time(float *data, int N, int (*bcast_function)(void*, int, MPI_Datatype, int, MPI_Comm));
int get_n_from_size(int N);

int MY_Bcast(void* buffer, int count, MPI_Datatype datatype, int root, MPI_Comm comm);

#endif // HEADERS_H