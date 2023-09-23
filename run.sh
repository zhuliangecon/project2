#!/bin/bash
make

mpirun -np 4 ./bcast_test
mpirun -np 5 ./bcast_test
mpirun -np 6 ./bcast_test
mpirun -np 7 ./bcast_test