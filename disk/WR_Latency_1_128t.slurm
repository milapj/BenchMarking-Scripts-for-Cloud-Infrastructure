#!/bin/bash
#SBATCH --nodes=1
#SBATCH --output=output/WRLatency1128.out
./DISKFIN disk-WR-1-128thread.dat
