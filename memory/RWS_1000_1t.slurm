#!/bin/bash
#SBATCH --nodes=1
#SBATCH --output=output/memory-RWS-1000-1thread.out
./RAMFIN memory-RWS-1000-1thread.dat
