#!/bin/bash
#SBATCH --nodes=1
#SBATCH --output=output/memory-RWR-1000000-4thread.out
./RAMFIN memory-RWR-1000000-4thread.dat
