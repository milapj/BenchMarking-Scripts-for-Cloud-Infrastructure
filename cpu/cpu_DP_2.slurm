#!/bin/bash

#SBATCH --nodes=01
#SBATCH --output=output/cpu_DP_2thread.out


echo $SLURM_JOB_NODELIST

./CPUFIN cpu_DP_2thread.dat 
