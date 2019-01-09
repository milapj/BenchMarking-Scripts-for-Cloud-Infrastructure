#!/bin/bash
#SBATCH --nodes=1
#SBATCH --output=output/WRLatency132.out
./DISKFIN disk-WR-1-32thread.dat
