#!/bin/bash
#SBATCH --nodes=1
#SBATCH --output=output/MyDiskBench-RR-10000-2.out
./DISKFIN disk-RR-10000-2thread.dat
