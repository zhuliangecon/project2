#!/bin/bash
make clean
make

for P in 2 3 4 5 6 
do
    echo "Testing with $P processes..."
    mpirun -np $P ./bcast_test
done