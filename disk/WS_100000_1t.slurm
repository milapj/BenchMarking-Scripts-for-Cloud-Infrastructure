#!/bin/bash
#SBATCH --nodes=1
#SBATCH --output=output/MyDiskBench-WS-100000-1.out
./DISKFIN disk-WS-100000-1thread.dat
