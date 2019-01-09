#!/bin/bash

#SBATCH --nodes=01
#SBATCH --output=output/cpu_SP_2thread.out


echo $SLURM_JOB_NODELIST

./CPUFIN cpu_SP_2thread.dat 
