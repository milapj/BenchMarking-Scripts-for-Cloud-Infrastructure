#!/bin/bash
#SBATCH --nodes=1
#SBATCH --output=output/MyDiskBench-RR-1000-1.out
./DISKFIN disk-RR-1000-1thread.dat
