#!/bin/bash
#SBATCH --nodes=1
#SBATCH --output=output/memory-RWS-1000-2thread.out
./RAMFIN memory-RWS-1000-2thread.dat
