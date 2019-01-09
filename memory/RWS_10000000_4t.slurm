#!/bin/bash
#SBATCH --nodes=1
#SBATCH --output=output/memory-RWS-10000000-4thread.out
./RAMFIN memory-RWS-10000000-4thread.dat
