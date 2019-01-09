#!/bin/bash
#SBATCH --nodes=1
#SBATCH --output=output/WRLatency14.out
./DISKFIN disk-WR-1-4thread.dat
