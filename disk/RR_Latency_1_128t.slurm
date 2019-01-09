#!/bin/bash
#SBATCH --nodes=1
#SBATCH --output=output/RRLatency1128.out
./DISKFIN disk-RR-1-128thread.dat
