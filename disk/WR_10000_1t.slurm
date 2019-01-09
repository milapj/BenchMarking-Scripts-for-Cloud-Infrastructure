#!/bin/bash
#SBATCH --nodes=1
#SBATCH --output=output/MyDiskBench-WR-10000-1.out
./DISKFIN disk-WR-10000-1thread.dat
