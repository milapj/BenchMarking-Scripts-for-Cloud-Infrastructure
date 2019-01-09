#!/bin/bash
#SBATCH --nodes=1
#SBATCH --output=output/MyDiskBench-WS-100000-2.out
./DISKFIN disk-WS-100000-2thread.dat
