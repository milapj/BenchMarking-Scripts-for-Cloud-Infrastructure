#!/bin/bash
#SBATCH --nodes=1
#SBATCH --output=output/MyDiskBench-WR-100000-2.out
./DISKFIN disk-WR-100000-2thread.dat
