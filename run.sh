#!/bin/bash


mpicc -o hello hello.c

time mpirun -np 4 ./hello