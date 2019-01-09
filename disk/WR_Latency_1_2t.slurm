#!/bin/bash
#SBATCH --nodes=1
#SBATCH --output=output/WRLatency12.out
./DISKFIN disk-WR-1-2thread.dat
