#!/bin/bash

#SBATCH --nodes=01
#SBATCH --output=output/cpu_HP_2thread.out


echo $SLURM_JOB_NODELIST

./CPUFIN cpu_HP_2thread.dat 
