#!/bin/bash
#SBATCH --nodes=1
#SBATCH --output=output/RRLatency116.out
./DISKFIN disk-RR-1-16thread.dat
