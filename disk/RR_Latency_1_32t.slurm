#!/bin/bash
#SBATCH --nodes=1
#SBATCH --output=output/RRLatency132.out
./DISKFIN disk-RR-1-32thread.dat
