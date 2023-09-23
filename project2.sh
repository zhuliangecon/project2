#!/bin/bash

#SBATCH -p short-40core
#SBATCH -N 1
#SBATCH --ntasks-per-node=40
#SBATCH --time=0:01:00
#SBATCH --job-name=project2 
#SBATCH --output=output.txt

# load module with MPI wrapper
module load openmpi/gcc12.1/4.1.4

# 执行 test.sh 脚本
./test.sh