#!/bin/bash
#SBATCH --nodes=1
#SBATCH --output=output/memory-RWR-1-2thread.out
./RAMFIN memory-RWR-1-2thread.dat
