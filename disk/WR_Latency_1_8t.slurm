#!/bin/bash
#SBATCH --nodes=1
#SBATCH --output=output/WRLatency18.out
./DISKFIN disk-WR-1-8thread.dat
