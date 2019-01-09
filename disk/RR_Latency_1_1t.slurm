#!/bin/bash
#SBATCH --nodes=1
#SBATCH --output=output/RRLatency11.out
./DISKFIN disk-RR-1-1thread.dat
