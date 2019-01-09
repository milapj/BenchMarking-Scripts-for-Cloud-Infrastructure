#!/bin/bash
#SBATCH --nodes=1
#SBATCH --output=output/WRLatency11.out
./DISKFIN disk-WR-1-1thread.dat
