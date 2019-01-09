#!/bin/bash
#SBATCH --nodes=1
#SBATCH --output=output/RRLatency14.out
./DISKFIN disk-RR-1-4thread.dat
