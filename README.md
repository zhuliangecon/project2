# Project 2: MPI Collective Operations
This repository contains the implementation and evaluation of custom MPI collective operations in comparison to MPI's default operations.

## Project Description
The goal of this project is to implement custom MPI collective operations and evaluate their performance in comparison to MPI's default operations. The custom collective operations are implemented in C and are based on MPI's default operations. The evaluation is done by comparing the execution time of the custom collective operations to the execution time of the default operations.

## Project Structure
```
project2/
│
├── headers.h              # Header file 
├── main.c                 # Main program entry
├── functions.c            # Implementation of functions
├── make                   # Makefile for building the project
├── test.sh                # Script for running on lcoal machine
├── project2.sh            # Script to execute the program on the cluster
└── README.md              # This documentation file

```

## How to run the program
The program can be executed on the cluster by running the script `project2.sh`. 
The script will compile the program and execute it. 

I used the following commands to run the program on the node `short-40core` on the `milan` login node:
```
module load slurm
cd project2
sbatch project2.sh
```
The results will be stored in the file `output.txt`.
