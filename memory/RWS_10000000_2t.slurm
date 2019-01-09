#!/bin/bash
#SBATCH --nodes=1
#SBATCH --output=output/memory-RWS-10000000-2thread.out
./RAMFIN memory-RWS-10000000-2thread.dat
