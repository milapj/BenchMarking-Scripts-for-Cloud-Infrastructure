#!/bin/bash
#SBATCH --nodes=1
#SBATCH --output=output/RRLatency18.out
./DISKFIN disk-RR-1-8thread.dat
