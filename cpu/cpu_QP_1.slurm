#!/bin/bash

#SBATCH --nodes=01
#SBATCH --output=output/cpu_QP_1thread.out


echo $SLURM_JOB_NODELIST

./CPUFIN cpu_QP_1thread.dat 
