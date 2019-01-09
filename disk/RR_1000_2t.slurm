#!/bin/bash
#SBATCH --nodes=1
#SBATCH --output=output/MyDiskBench-RR-1000-2.out
./DISKFIN disk-RR-1000-2thread.dat
