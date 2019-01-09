#!/bin/bash
#SBATCH --nodes=1
#SBATCH --output=output/memory-RWS-1-1thread.out
./RAMFIN memory-RWS-1-1thread.dat
