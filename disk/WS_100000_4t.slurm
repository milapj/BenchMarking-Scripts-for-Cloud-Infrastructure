#!/bin/bash
#SBATCH --nodes=1
#SBATCH --output=output/MyDiskBench-WS-100000-4.out
./DISKFIN disk-WS-100000-4thread.dat
