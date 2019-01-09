#!/bin/bash
#SBATCH --nodes=1
#SBATCH --output=output/MyDiskBench-WS-1000-1.out
./DISKFIN disk-WS-1000-1thread.dat
