#!/bin/bash
#SBATCH --nodes=1
#SBATCH --output=output/MyDiskBench-WR-10000-2.out
./DISKFIN disk-WR-10000-2thread.dat
