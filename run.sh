#!/bin/bash


mpicc -o bcast_test main.c -lm

mpirun -np 4 ./bcast_test