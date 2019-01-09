#!/bin/bash
#SBATCH --nodes=1
#SBATCH --output=output/memory-RWR-10000000-1thread.out
./RAMFIN memory-RWR-10000000-1thread.dat
