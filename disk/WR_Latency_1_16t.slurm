#!/bin/bash
#SBATCH --nodes=1
#SBATCH --output=output/WRLatency116.out
./DISKFIN disk-WR-1-16thread.dat
