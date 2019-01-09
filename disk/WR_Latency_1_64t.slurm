#!/bin/bash
#SBATCH --nodes=1
#SBATCH --output=output/WRLatency164.out
./DISKFIN disk-WR-1-64thread.dat
