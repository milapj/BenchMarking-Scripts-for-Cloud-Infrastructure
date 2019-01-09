#!/bin/bash
#SBATCH --nodes=1
#SBATCH --output=output/memory-RWS-1-4thread.out
./RAMFIN memory-RWS-1-4thread.dat
