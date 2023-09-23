#!/bin/bash
make

for P in 4 7 28 37
do
    echo "Testing with $P processes..."
    mpirun -np $P ./bcast_test
done