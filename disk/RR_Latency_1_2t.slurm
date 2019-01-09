#!/bin/bash
#SBATCH --nodes=1
#SBATCH --output=output/RRLatency12.out
./DISKFIN disk-RR-1-2thread.dat
