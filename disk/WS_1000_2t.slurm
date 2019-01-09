#!/bin/bash
#SBATCH --nodes=1
#SBATCH --output=output/MyDiskBench-WS-1000-2.out
./DISKFIN disk-WS-1000-2thread.dat
