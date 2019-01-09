#!/bin/bash
#SBATCH --nodes=1
#SBATCH --output=output/MyDiskBench-WS-10000-2.out
./DISKFIN disk-WS-10000-2thread.dat
