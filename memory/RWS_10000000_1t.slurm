#!/bin/bash
#SBATCH --nodes=1
#SBATCH --output=output/memory-RWS-10000000-1thread.out
./RAMFIN memory-RWS-10000000-1thread.dat
