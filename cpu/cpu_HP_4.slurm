#!/bin/bash

#SBATCH --nodes=01
#SBATCH --output=output/cpu_HP_4thread.out


echo $SLURM_JOB_NODELIST

./CPUFIN cpu_HP_4thread.dat 
