#!/bin/bash
#SBATCH --nodes=1
#SBATCH --output=output/MyDiskBench-RR-100000-1.out
./DISKFIN disk-RR-100000-1thread.dat
