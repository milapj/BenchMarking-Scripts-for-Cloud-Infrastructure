#!/bin/bash
#SBATCH --nodes=1
#SBATCH --output=output/MyDiskBench-WS-10000-1.out
./DISKFIN disk-WS-10000-1thread.dat
