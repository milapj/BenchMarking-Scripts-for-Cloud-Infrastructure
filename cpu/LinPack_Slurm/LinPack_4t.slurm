#!/bin/bash

#SBATCH --nodes=01
#SBATCH --output=cpu_HPL_4thread.out


echo $SLURM_JOB_NODELIST

./runme_xeon64
