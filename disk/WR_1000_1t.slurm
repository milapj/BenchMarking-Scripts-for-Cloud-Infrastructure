#!/bin/bash
#SBATCH --nodes=1
#SBATCH --output=output/MyDiskBench-WR-1000-1.out
./DISKFIN disk-WR-1000-1thread.dat
