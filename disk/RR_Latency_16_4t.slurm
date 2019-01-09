#!/bin/bash
#SBATCH --nodes=1
#SBATCH --output=output/RRLatency164.out
./DISKFIN disk-RR-1-64thread.dat
